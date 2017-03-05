#pragma once
#include <vector>


namespace cds {
    class compressed_bit_vector {
    public:
        std::vector<std::vector<unsigned int> > combinations;

        void compute_combinations(unsigned int size);
    };
}
