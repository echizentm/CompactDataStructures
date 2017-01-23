#include <cmath>
#include "dense_pointers.h"


namespace cds {
    using namespace std;

    dense_pointers::dense_pointers(
        unsigned int max_length, unsigned int rate
    ) : offsets(ceil(log2(rate - 1) * max_length)) {
        this->rate = rate;
        this->size = 0;
    }

    unsigned int dense_pointers::vector_size() {
        return this->bv.vector_size() +
               this->offsets.vector_size() +
               this->samples.size();
    }

    unsigned int dense_pointers::read(unsigned int index) {
        return 0;
    }

    void dense_pointers::push_back(unsigned int value) {

    }
}
