#pragma once
#include <vector>
#include "bit_vector.h"


namespace cds {
    class sampled_pointers {
        bit_vector bv;
        std::vector<unsigned int> samples;

    public:
        unsigned int rate;
        unsigned int size;

        sampled_pointers(unsigned int rate = 4);

        unsigned int vector_size();
        unsigned int read(unsigned int index);
        void push_back(unsigned int value);
    };
}
