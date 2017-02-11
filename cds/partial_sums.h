#pragma once
#include <vector>
#include "fixed_length_vector.h"


namespace cds {
    class partial_sums : public fixed_length_vector {
        std::vector<unsigned int> samples;

    public:
        unsigned int rate;

        partial_sums(
            unsigned int length,
            unsigned int rate = 4,
            unsigned int size = 0,
            bool is_rapid = false
        );

        void resize(unsigned int size);
        unsigned int vector_size();
        void write(unsigned int index, unsigned int value);

        unsigned int sum(unsigned int index);
        unsigned int search(unsigned int value);
    };
}
