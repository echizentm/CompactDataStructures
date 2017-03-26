#pragma once
#include <vector>
#include "fixed_length_vector.h"


namespace cds {
    class partial_sums : public fixed_length_vector {
        std::vector<uint64_t> samples;

    public:
        uint64_t rate;

        partial_sums(
            uint64_t length,
            uint64_t rate = 4,
            uint64_t size = 0,
            bool is_rapid = false
        );

        void resize(uint64_t size);
        uint64_t vector_size();
        void write(uint64_t index, uint64_t value);

        uint64_t sum(uint64_t index);
        uint64_t search(uint64_t value);
    };
}
