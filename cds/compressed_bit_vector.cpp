#include "compressed_bit_vector.h"


namespace cds {
    using namespace std;

    void compressed_bit_vector::compute_combinations(unsigned int block_size) {
        this->combinations.resize(block_size);
        for (unsigned int i = 0; i < this->combinations.size(); i++) {
            this->combinations[i].resize(block_size + 1);
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
    }

    compressed_bit_vector::compressed_bit_vector(unsigned int block_size) {
        this->block_size = block_size;
        this->compute_combinations(this->block_size);
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
}
