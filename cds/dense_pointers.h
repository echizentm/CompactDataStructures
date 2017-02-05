#pragma once
#include <vector>
#include "bit_vector.h"
#include "fixed_length_vector.h"


namespace cds {
    class dense_pointers {
        bit_vector bv;
        fixed_length_vector offsets;
        std::vector<unsigned int> samples;

    public:
        unsigned int rate;
        unsigned int size;

        dense_pointers(unsigned int max_length, unsigned int rate = 4);

        unsigned int vector_size();
        unsigned int read(unsigned int index);
        void push_back(unsigned int value);
    };
}
