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

    const bit_vector &compressed_bit_vector::decode(unsigned int cclass, unsigned int offset) {
        this->decoded_bv.bits_write(0, this->decoded_bv.size, 0);
        unsigned int index = 0;
        while (cclass > 0) {
            if (offset >= this->combinations[this->block_size - index - 1][cclass]) {
                this->decoded_bv.bit_set(index);
                offset -= this->combinations[this->block_size - index - 1][cclass];
                cclass--;
            }
            index++;
        }
        return this->decoded_bv;
    }


    compressed_bit_vector::compressed_bit_vector(
        const bit_vector& bv, unsigned int sampling_rate
    ) {
        this->sampling_rate = sampling_rate;
        this->compute_combinations(this->block_size);
        this->decoded_bv.resize(this->block_size);

        this->size = bv.size;
        this->classes.resize(ceil(this->size / this->block_size));
        for (unsigned int i = 0; i < this->classes.size(); i++) {
            pair<unsigned int, unsigned int> encoded = this->encode(
                bv, i * this->block_size, (i + 1) * this->block_size
            );

            this->classes[i] = encoded.first;

            unsigned int begin = this->offsets.size;
            unsigned int end = this->offsets.size + this->offset_bits[encoded.first];
            if (begin < end) {
                this->offsets.resize(end);
                this->offsets.bits_write(begin, end, encoded.second);
            }

            if ((i % this->sampling_rate) == 0) {
                this->offset_samples.push_back(begin);
            }
        }
    }

    unsigned int compressed_bit_vector::vector_size() {
        unsigned int combinations_size = 0;
        for (auto e : this->combinations) { combinations_size += e.size(); }
        return combinations_size + this->offset_bits.size() + this->offset_samples.size() +
               this->classes.size() * sizeof(unsigned char) / sizeof(unsigned int) + this->offsets.vector_size();
    }

    unsigned int compressed_bit_vector::access(unsigned int index) {
        unsigned int sample_index = index / this->block_size / this->sampling_rate;
        unsigned int begin = this->offset_samples[sample_index];
        unsigned int end = begin;
        unsigned int cclass = 0;
        for (unsigned int i = sample_index * this->sampling_rate; i <= (index / this->block_size); i++) {
            cclass = this->classes[i];
            begin = end;
            end += this->offset_bits[cclass];
        }
        unsigned int offset = (begin == end) ? 0 : this->offsets.bits_read(begin, end);
        return this->decode(cclass, offset).bit_read(index % this->block_size);
    }
}
