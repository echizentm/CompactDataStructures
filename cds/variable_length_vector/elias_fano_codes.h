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

        uint64_t vector_size() const;
        uint64_t read(uint64_t index) const;
        void push_back(uint64_t value);
    };
}
