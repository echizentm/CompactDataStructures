#pragma once
#include <vector>
#include "../fixed_length_vector.h"
#include "../partial_sums.h"
#include "base.h"


namespace cds {
    class direct_access_codes : virtual public variable_length_vector {
        std::vector<partial_sums> markers;
        std::vector<fixed_length_vector> blocks;

    public:
        uint64_t length;

        direct_access_codes(uint64_t length);

        uint64_t vector_size();
        uint64_t read(uint64_t index);
        void push_back(uint64_t value);
    };
}
