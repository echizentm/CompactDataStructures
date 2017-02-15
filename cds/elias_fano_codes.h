#pragma once
#include "bit_vector.h"
#include "partial_sums.h"


namespace cds {
    class elias_fano_codes {
        bit_vector bv;
        partial_sums marker;

    public:
        unsigned int size;

        elias_fano_codes();

        unsigned int vector_size();
        unsigned int read(unsigned int index);
        void push_back(unsigned int value);
    };
}
