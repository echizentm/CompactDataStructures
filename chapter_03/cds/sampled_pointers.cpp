#include "sampled_pointers.h"


namespace cds {
    sampled_pointers::sampled_pointers(unsigned int rate) {
        this->rate = rate;
        this->size = 0;
    }

    unsigned int sampled_pointers::vector_size() {
        return this->bv.vector_size() + this->samples.size();
    }

    unsigned int sampled_pointers::read(unsigned int index) {
        unsigned int begin = this->samples[index / this->rate];
        unsigned int values_to_read = index % this->rate;

        while (true) {
            unsigned int zeros_length = 0;
            while (this->bv.bit_read(begin) == 0) {
                zeros_length++;
                begin++;
            }
            unsigned int end = begin + zeros_length + 1;

            if (values_to_read == 0) {
                return this->bv.bits_read(begin, end, true) - 1;
            }
            values_to_read -= 1;
            begin = end;
        }
    }

    void sampled_pointers::push_back(unsigned int value) {
        if (this->size % this->rate == 0) {
            this->samples.push_back(this->bv.size);
        }
        this->size++;

        value += 1;
        unsigned int value_dummy = value;
        unsigned int value_length = 0;
        while (value_dummy != 0) {
            value_dummy >>= 1;
            value_length++;
        }

        unsigned int begin = this->bv.size + value_length - 1;
        unsigned int end = begin + value_length;

        this->bv.resize(end);
        this->bv.bits_write(begin, end, value, true);
    }
}
