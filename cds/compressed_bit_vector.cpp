#include <cmath>
#include "compressed_bit_vector.h"


namespace cds {
    using namespace std;

    void compressed_bit_vector::compute_combinations(uint64_t block_size) {
        this->combinations.resize(block_size + 1);
        for (uint64_t i = 0; i < this->combinations.size(); i++) {
            this->combinations[i].resize(this->combinations.size());
            this->combinations[i][0] = 1;
            this->combinations[i][i] = 1;
        }

        for (uint64_t i = 2; i < this->combinations.size(); i++) {
            for (uint64_t j = 1; j < i; j++) {
                this->combinations[i][j] =
                    this->combinations[i - 1][j - 1] +
                    this->combinations[i - 1][j];
            }
        }

        this->offset_bits.resize(this->combinations.size());
        for (uint64_t i = 0; i < this->offset_bits.size(); i++) {
            this->offset_bits[i] = ceil(log2(this->combinations[block_size][i]));
        }
    }

    pair<uint64_t, uint64_t> compressed_bit_vector::encode(const bit_vector &bv, uint64_t begin, uint64_t end) const {
        uint64_t cclass = 0;
        for (uint64_t i = begin; i < end; i++) {
            cclass += bv.bit_read(i);
        }

        uint64_t offset = 0;
        uint64_t class_tmp = cclass;
        while ((class_tmp > 0) && (class_tmp <= (end - begin - 1))) {
            if (bv.bit_read(begin) == 1) {
                offset += this->combinations[end - begin - 1][class_tmp];
                class_tmp--;
            }
            begin++;
        }
        return pair<uint64_t, uint64_t>(cclass, offset);
    }

    uint64_t compressed_bit_vector::decode(uint64_t cclass, uint64_t offset, uint64_t index) const {
        uint64_t index_tmp = 0;
        while (cclass > 0) {
            uint64_t bit = 0;
            if (offset >= this->combinations[this->block_size - index_tmp - 1][cclass]) {
                offset -= this->combinations[this->block_size - index_tmp - 1][cclass];
                cclass--;
                bit = 1;
            }
            if (index_tmp == index) { return bit; }
            index_tmp++;
        }
        return 0;
    }


    compressed_bit_vector::compressed_bit_vector(const bit_vector& bv) {
        this->compute_combinations(this->block_size);

        this->size = bv.size;
        this->classes.resize(ceil(this->size / this->block_size));
        for (uint64_t i = 0; i < this->classes.size(); i++) {
            pair<uint64_t, uint64_t> encoded = this->encode(
                bv, i * this->block_size, (i + 1) * this->block_size
            );

            this->classes[i] = encoded.first;

            uint64_t begin = this->offsets.size;
            uint64_t end = this->offsets.size + this->offset_bits[encoded.first];
            if (begin < end) {
                this->offsets.resize(end);
                this->offsets.bits_write(begin, end, encoded.second);
            }

            if ((i % this->sampling_rate) == 0) {
                this->offset_samples.push_back(begin);
            }
        }
    }

    uint64_t compressed_bit_vector::vector_size() const {
        uint64_t combinations_size = 0;
        for (auto e : this->combinations) { combinations_size += e.size(); }
        return combinations_size + this->offset_bits.size() + this->offset_samples.size() +
               this->classes.size() * sizeof(uint8_t) / sizeof(uint64_t) + this->offsets.vector_size();
    }

    uint64_t compressed_bit_vector::access(uint64_t index) const {
        uint64_t sample_index = index / this->block_size / this->sampling_rate;
        uint64_t begin = this->offset_samples[sample_index];
        uint64_t end = begin;
        uint64_t cclass = 0;
        for (uint64_t i = sample_index * this->sampling_rate; i <= (index / this->block_size); i++) {
            cclass = this->classes[i];
            begin = end;
            end += this->offset_bits[cclass];
        }
        return this->decode(
            cclass,
            (begin == end) ? 0 : this->offsets.bits_read(begin, end),
            index % this->block_size
        );
    }
}
