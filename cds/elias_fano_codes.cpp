#include "elias_fano_codes.h"


namespace cds {
    elias_fano_codes::elias_fano_codes() : marker(1) {
        this->size = 0;
        this->marker.resize(1);
        this->marker.write(0, 1);
    }

    unsigned int elias_fano_codes::vector_size() {
        return this->bv.vector_size() + this->marker.vector_size();
    }

    unsigned int elias_fano_codes::read(unsigned int index) {
        unsigned int begin = this->marker.search(index + 1);
        unsigned int end = this->marker.search(index + 2);

        unsigned int value = this->bv.bits_read(begin, end);
        return (value | (1 << (end - begin))) - 2;
    }

    void elias_fano_codes::push_back(unsigned int value) {
        this->size++;

        value += 2;
        unsigned int length = bits_length(value) - 1;
        value &= ((1 << length) - 1);
        this->bv.resize(this->bv.size + length);
        this->marker.resize(this->marker.size + length);

        this->bv.bits_write(this->bv.size - length, this->bv.size, value);
        this->marker.write(this->marker.size - 1, 1);
    }
}
