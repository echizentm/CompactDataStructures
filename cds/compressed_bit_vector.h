#pragma once
#include <vector>
#include <map>
#include "bit_vector.h"


namespace cds {
    class compressed_bit_vector {
        std::vector<std::vector<unsigned int> > combinations;

        void compute_combinations(unsigned int block_size);

    public:
        unsigned int block_size;

        compressed_bit_vector(unsigned int block_size = 4);

        std::pair<unsigned int, unsigned int> encode(
            const bit_vector &bv, unsigned int begin, unsigned int end
        );
        bit_vector decode(unsigned int cclass, unsigned int offset);
    };
}
