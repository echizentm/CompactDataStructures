#pragma once
#include "../bit_vector.h"
#include "../partial_sums.h"
#include "base.h"


namespace cds {
    class elias_fano_codes : virtual public variable_length_vector {
        bit_vector bv;
        partial_sums marker;

    public:
        elias_fano_codes();

        unsigned int vector_size();
        unsigned int read(unsigned int index);
        void push_back(unsigned int value);
    };
}
