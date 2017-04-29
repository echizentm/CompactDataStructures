#include "compressed_bit_vector_rank.h"
#include <iostream>
using namespace std;


namespace cds {
    compressed_bit_vector_rank::compressed_bit_vector_rank(const bit_vector& bv)
    : compressed_bit_vector(bv) {
        if (this->classes.size() == 0) { return; }

        this->rank_samples.resize((this->classes.size() - 1) / this->sampling_rate + 2);
        uint64_t rank = 0;
        for (uint64_t i = 0; i < this->classes.size(); i++) {
            rank += this->classes[i];
            this->rank_samples[i / this->sampling_rate + 1] = rank;
        }
    }

    uint64_t compressed_bit_vector_rank::vector_size() const {
        return compressed_bit_vector::vector_size() + this->rank_samples.size();
    }

    uint64_t compressed_bit_vector_rank::rank(uint64_t index) const {
        uint64_t sample_index = index / this->block_size / this->sampling_rate;
        uint64_t rank = this->rank_samples[sample_index];
        uint64_t begin = this->offset_samples[sample_index];
        uint64_t end = begin;
        uint64_t cclass = 0;
        for (uint64_t i = sample_index * this->sampling_rate; i <= (index / this->block_size); i++) {
            rank += cclass;
            cclass = this->classes[i];
            begin = end;
            end += this->offset_bits[cclass];
        }
        return rank + this->decode(
            cclass,
            (begin == end) ? 0 : this->offsets.bits_read(begin, end),
            index % this->block_size,
            true
        );
    }
}
