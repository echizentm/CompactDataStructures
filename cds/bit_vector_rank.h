#pragma once
#include <vector>
#include "bit_vector.h"


namespace cds {
    uint64_t popcount(uint64_t bits);

    class bit_vector_rank : public bit_vector {
        std::vector<uint64_t> samples;

    public:
        uint64_t rate;

        bit_vector_rank(uint64_t rate = 4, uint64_t size = 0);

        void resize(uint64_t size);
        uint64_t vector_size() const;
        void bit_set(uint64_t index);
        void bit_clear(uint64_t index);

        uint64_t rank(uint64_t index) const;
        uint64_t rank_naive(uint64_t index) const;
    };
};
