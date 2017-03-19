#include <cmath>
#include "compressed_bit_vector.h"


namespace cds {
    using namespace std;

    void compressed_bit_vector::compute_combinations(unsigned int block_size) {
        this->combinations.resize(block_size + 1);
        for (unsigned int i = 0; i < this->combinations.size(); i++) {
            this->combinations[i].resize(this->combinations.size());
            this->combinations[i][0] = 1;
            this->combinations[i][i] = 1;
        }

        for (unsigned int i = 2; i < this->combinations.size(); i++) {
            for (unsigned int j = 1; j < i; j++) {
                this->combinations[i][j] =
                    this->combinations[i - 1][j - 1] +
                    this->combinations[i - 1][j];
            }
        }

        this->offset_bits.resize(this->combinations.size());
        for (unsigned int i = 0; i < this->offset_bits.size(); i++) {
            this->offset_bits[i] = ceil(log2(this->combinations[block_size][i]));
        }
    }

    pair<unsigned int, unsigned int> compressed_bit_vector::encode(
        const bit_vector &bv, unsigned int begin, unsigned int end
    ) {
        unsigned int cclass = 0;
        for (unsigned int i = begin; i < end; i++) {
            cclass += bv.bit_read(i);
        }

        unsigned int offset = 0;
        unsigned int class_tmp = cclass;
        while ((class_tmp > 0) && (class_tmp <= (end - begin - 1))) {
            if (bv.bit_read(begin) == 1) {
                offset += this->combinations[end - begin - 1][class_tmp];
                class_tmp--;
            }
            begin++;
        }
        return pair<unsigned int, unsigned int>(cclass, offset);
    }

    bit_vector compressed_bit_vector::decode(unsigned int cclass, unsigned int offset) {
        bit_vector bv(this->block_size);
        unsigned int index = 0;
        while (cclass > 0) {
            if (offset >= this->combinations[this->block_size - index - 1][cclass]) {
                bv.bit_set(index);
                offset -= this->combinations[this->block_size - index - 1][cclass];
                cclass--;
            }
            index++;
        }
        return bv;
    }


    compressed_bit_vector::compressed_bit_vector(
        const bit_vector& bv, unsigned int block_size
    ) : classes(ceil(log2(block_size + 1))) {
        this->block_size = block_size;
        this->compute_combinations(this->block_size);

        this->size = bv.size;
        this->classes.resize(ceil(this->size / this->block_size ));
        for (unsigned int i = 0; i < this->classes.size; i++) {
            pair<unsigned int, unsigned int> encoded = this->encode(
                bv, i * this->block_size, (i + 1) * this->block_size
            );

            this->classes.write(i, encoded.first);

            unsigned int begin = this->offsets.size;
            unsigned int end = this->offsets.size + this->offset_bits[encoded.first];
            this->offsets.resize(end);
            this->offsets.bits_write(begin, end, encoded.second);
        }
    }

    unsigned int compressed_bit_vector::vector_size() {
        return this->classes.vector_size() + this->offsets.vector_size();
    }

    unsigned int compressed_bit_vector::access(unsigned int index) {
        unsigned int begin = 0;
        unsigned int end = 0;
        for (unsigned int i = 0; i <= ceil(index / this->block_size); i++) {
            begin = end;
            end += this->offset_bits[this->classes.read(i)];
        }
        unsigned int cclass = this->classes.read(ceil(index / this->block_size));
        unsigned int offset = (begin == end) ? 0 : this->offsets.bits_read(begin, end);
        return this->decode(cclass, offset).bit_read(index % this->block_size);
    }
}
