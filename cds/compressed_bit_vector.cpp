#include "compressed_bit_vector.h"


namespace cds {
    void compressed_bit_vector::compute_combinations(unsigned int size) {
        this->combinations.resize(size);
        for (unsigned int i = 0; i < this->combinations.size(); i++) {
            this->combinations[i].resize(i + 1);
            this->combinations[i][0] = 1;
            this->combinations[i][i] = 1;
        }

        for (unsigned int i = 2; i < this->combinations.size(); i++) {
            for (unsigned int j = 1; j < i; j++) {
                this->combinations[i][j] =
                    this->combinations[i - 1][j - 1] +
                    this->combinations[i - 1][j];
            }
        }
    }
}
