#include "sampled_pointers.h"


namespace cds {
    sampled_pointers::sampled_pointers(unsigned int rate) {
        this->rate = rate;
        this->size = 0;
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
                return this->bits_reverse(this->bv.bits_read(begin, end), end - begin) - 1;
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
        this->bv.bits_write(begin, end, this->bits_reverse(value, end - begin));
    }

    unsigned int sampled_pointers::bits_reverse(
        unsigned int value, unsigned int length
    ) {
        unsigned int reversed = 0;
        while (length > 0) {
            reversed <<= 1;
            reversed |= (value & 1);
            value >>= 1;
            length -= 1;
        }
        return reversed;
    }
}
