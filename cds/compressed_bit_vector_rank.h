#pragma once
#include <vector>
#include "compressed_bit_vector.h"


namespace cds {
    class compressed_bit_vector_rank : public compressed_bit_vector {
        std::vector<uint64_t> rank_samples;

    public:
        compressed_bit_vector_rank(const bit_vector& bv);

        uint64_t vector_size() const;
        uint64_t rank(uint64_t index) const;

        uint64_t select(uint64_t value) const;
    };
}
