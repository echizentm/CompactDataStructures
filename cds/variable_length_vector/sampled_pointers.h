#pragma once
#include <vector>
#include "../bit_vector.h"
#include "base.h"


namespace cds {
    class sampled_pointers : virtual public variable_length_vector {
        bit_vector bv;
        std::vector<unsigned int> samples;

    public:
        unsigned int rate;

        sampled_pointers(unsigned int rate = 4);

        unsigned int vector_size();
        unsigned int read(unsigned int index);
        void push_back(unsigned int value);
    };
}
