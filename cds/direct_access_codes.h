#pragma once
#include <vector>
#include "fixed_length_vector.h"
#include "partial_sums.h"


namespace cds {
    class direct_access_codes {
    public:
        direct_access_codes(unsigned int length, unsigned int size = 0);

        void resize(unsigned int size);
        unsigned int vector_size();
        unsigned int read(unsigned int index);
        void write(unsigned int index, unsigned int value);
    };
}
