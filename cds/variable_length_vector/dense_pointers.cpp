#include <cmath>
#include "dense_pointers.h"


namespace cds {
    using namespace std;

    dense_pointers::dense_pointers(
        unsigned int max_length, unsigned int rate
    ) : offsets(ceil(log2((rate - 1) * max_length))) {
        this->rate = rate;
        this->size = 0;
    }

    unsigned int dense_pointers::vector_size() {
        return this->bv.vector_size() +
               this->offsets.vector_size() +
               this->samples.size();
    }

    unsigned int dense_pointers::read(unsigned int index) {
        unsigned int begin = this->samples[index / this->rate] +
                             this->offsets.read(index);
        unsigned int end = this->bv.size;
        index++;

        if (index < this->offsets.size) {
            end = this->samples[index / this->rate] +
                  this->offsets.read(index);
        }
        if (begin == end) {
            return 0;
        }

        return (
            this->bv.bits_read(begin, end) | (1 << (end - begin))
        ) - 1;
    }

    void dense_pointers::push_back(unsigned int value) {
        if (this->size % this->rate == 0) {
            this->samples.push_back(this->bv.size);
        }

        this->offsets.resize(this->size + 1);
        this->offsets.write(
            this->size,
            this->bv.size - this->samples[this->size / this->rate]
        );
        this->size++;

        value++;
        unsigned int value_length = bits_length(value) - 1;
        if (value_length == 0) {
            return;
        }
        value &= ~(1 << value_length);

        unsigned int begin = this->bv.size;
        unsigned int end = begin + value_length;

        this->bv.resize(end);
        this->bv.bits_write(begin, end, value);
    }
}
