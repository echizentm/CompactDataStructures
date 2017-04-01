#include "elias_fano_codes.h"


namespace cds {
    elias_fano_codes::elias_fano_codes() : marker(1) {
        this->size = 0;
        this->marker.resize(1);
        this->marker.write(0, 1);
    }

    uint64_t elias_fano_codes::vector_size() const {
        return this->bv.vector_size() + this->marker.vector_size();
    }

    uint64_t elias_fano_codes::read(uint64_t index) const {
        uint64_t begin = this->marker.search(index + 1);
        uint64_t end = this->marker.search(index + 2);

        uint64_t value = this->bv.bits_read(begin, end);
        return (value | (1LL << (end - begin))) - 2;
    }

    void elias_fano_codes::push_back(uint64_t value) {
        this->size++;

        value += 2;
        uint64_t length = bits_length(value) - 1;
        value &= ((1LL << length) - 1);
        this->bv.resize(this->bv.size + length);
        this->marker.resize(this->marker.size + length);

        this->bv.bits_write(this->bv.size - length, this->bv.size, value);
        this->marker.write(this->marker.size - 1, 1);
    }
}
