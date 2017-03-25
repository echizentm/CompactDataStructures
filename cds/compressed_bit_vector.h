#pragma once
#include <vector>
#include <map>
#include "bit_vector.h"


namespace cds {
    class compressed_bit_vector {
        std::vector<std::vector<unsigned int> > combinations;
        std::vector<unsigned int> offset_bits;
        std::vector<unsigned int> offset_samples;
        std::vector<unsigned char> classes;
        bit_vector offsets;

        void compute_combinations(unsigned int block_size);

        std::pair<unsigned int, unsigned int> encode(
            const bit_vector &bv, unsigned int begin, unsigned int end
        );
        unsigned int decode(unsigned int cclass, unsigned int offset, unsigned int index);

    public:
        unsigned int block_size = sizeof(unsigned int) * 8 - 1;
        unsigned int sampling_rate;
        unsigned int size;

        compressed_bit_vector(const bit_vector& bv, unsigned int sampling_rate = 32);

        unsigned int vector_size();
        unsigned int access(unsigned int index);
    };
}
