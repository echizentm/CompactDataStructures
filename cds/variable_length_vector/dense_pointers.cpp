#include <cmath>
#include "dense_pointers.h"


namespace cds {
    using namespace std;

    dense_pointers::dense_pointers(uint64_t max_length, uint64_t rate)
    : offsets(ceil(log2((rate - 1) * max_length))) {
        this->rate = rate;
        this->size = 0;
    }

    uint64_t dense_pointers::vector_size() const {
        return this->bv.vector_size() +
               this->offsets.vector_size() +
               this->samples.size();
    }

    uint64_t dense_pointers::read(uint64_t index) const {
        uint64_t begin = this->samples[index / this->rate] +
                             this->offsets.read(index);
        uint64_t end = this->bv.size;
        index++;

        if (index < this->offsets.size) {
            end = this->samples[index / this->rate] +
                  this->offsets.read(index);
        }
        if (begin == end) {
            return 0;
        }

        return (
            this->bv.bits_read(begin, end) | (1LL << (end - begin))
        ) - 1;
    }

    void dense_pointers::push_back(uint64_t value) {
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
        uint64_t value_length = bits_length(value) - 1;
        if (value_length == 0) {
            return;
        }
        value &= ~(1LL << value_length);

        uint64_t begin = this->bv.size;
        uint64_t end = begin + value_length;

        this->bv.resize(end);
        this->bv.bits_write(begin, end, value);
    }
}
