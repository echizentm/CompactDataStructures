#pragma once
#include <vector>
#include <map>
#include "bit_vector.h"


namespace cds {
    class compressed_bit_vector {
    public:
        std::vector<std::vector<unsigned int> > combinations;

        void compute_combinations(unsigned int size);
        std::pair<unsigned int, unsigned int> encode(
            const bit_vector &bv, unsigned int begin, unsigned int end
        );
    };
}
