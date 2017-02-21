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
        unsigned int length;

        direct_access_codes(unsigned int length);

        unsigned int vector_size();
        unsigned int read(unsigned int index);
        void push_back(unsigned int value);
    };
}