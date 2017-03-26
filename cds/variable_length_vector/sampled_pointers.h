#pragma once
#include <vector>
#include "../bit_vector.h"
#include "base.h"


namespace cds {
    class sampled_pointers : virtual public variable_length_vector {
        bit_vector bv;
        std::vector<uint64_t> samples;

    public:
        uint64_t rate;

        sampled_pointers(uint64_t rate = 4);

        uint64_t vector_size();
        uint64_t read(uint64_t index);
        void push_back(uint64_t value);
    };
}
