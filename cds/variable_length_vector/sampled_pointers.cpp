#include "sampled_pointers.h"


namespace cds {
    sampled_pointers::sampled_pointers(uint64_t rate) {
        this->rate = rate;
        this->size = 0;
    }

    uint64_t sampled_pointers::vector_size() const {
        return this->bv.vector_size() + this->samples.size();
    }

    uint64_t sampled_pointers::read(uint64_t index) const {
        uint64_t begin = this->samples[index / this->rate];
        uint64_t values_to_read = index % this->rate;

        while (true) {
            uint64_t zeros_length = 0;
            while (this->bv.bit_read(begin) == 0) {
                zeros_length++;
                begin++;
            }
            uint64_t end = begin + zeros_length + 1;

            if (values_to_read == 0) {
                return this->bv.bits_read(begin, end, true) - 1;
            }
            values_to_read--;
            begin = end;
        }
    }

    void sampled_pointers::push_back(uint64_t value) {
        if (this->size % this->rate == 0) {
            this->samples.push_back(this->bv.size);
        }
        this->size++;

        value++;
        uint64_t value_length = bits_length(value);

        uint64_t begin = this->bv.size + value_length - 1;
        uint64_t end = begin + value_length;

        this->bv.resize(end);
        this->bv.bits_write(begin, end, value, true);
    }
}
