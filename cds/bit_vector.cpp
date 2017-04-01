#include "bit_vector.h"


namespace cds {
    uint64_t bits_reverse(uint64_t value, uint64_t length) {
        uint64_t reversed = 0;
        while (length > 0) {
            reversed <<= 1;
            reversed |= (value & 1);
            value >>= 1;
            length--;
        }
        return reversed;
    }

    uint64_t bits_length(uint64_t value) {
        uint64_t length = 0;
        while (value != 0) {
            value >>= 1;
            length++;
        }
        return length;
    }


    bit_vector::bit_vector(uint64_t size) {
        this->resize(size);
    }

    void bit_vector::resize(uint64_t size) {
        this->size = size;
        if (this->size > 0) {
            this->vec.resize((this->size - 1) / this->cell_size + 1);
        };
    }

    uint64_t bit_vector::vector_size() const {
        return this->vec.size();
    }

    uint64_t bit_vector::bit_read(uint64_t index) const {
        return this->vec[index / this->cell_size] >> (index % this->cell_size) & 1;
    }

    void bit_vector::bit_set(uint64_t index) {
        this->vec[index / this->cell_size] |= (1LL << (index % this->cell_size));
    }

    void bit_vector::bit_clear(uint64_t index) {
        this->vec[index / this->cell_size] &= ~(1LL << (index % this->cell_size));
    }


    uint64_t bit_vector::bits_read(uint64_t begin, uint64_t end, bool is_bits_reverse) const {
        if (this->is_in_a_cell(begin, end)) {
            return this->bits_read_from_a_cell(begin, end, is_bits_reverse);
        } else {
            return this->bits_read_from_two_cells(begin, end, is_bits_reverse);
        }
    }

    void bit_vector::bits_write(uint64_t begin, uint64_t end, uint64_t value, bool is_bits_reverse) {
        if (this->is_in_a_cell(begin, end)) {
            this->bits_write_to_a_cell(begin, end, value, is_bits_reverse);
        } else {
            this->bits_write_to_two_cells(begin, end, value, is_bits_reverse);
        }
    }


    bool bit_vector::is_in_a_cell(uint64_t begin, uint64_t end) const {
        return ((begin / this->cell_size) == ((end - 1) / this->cell_size));
    }

    uint64_t bit_vector::bits_read_from_a_cell(uint64_t begin, uint64_t end, bool is_bits_reverse) const {
       uint64_t value = this->vec[(end - 1) / this->cell_size] >> (begin % this->cell_size);
       if ((end - begin) < this->cell_size) { value &= ((1LL << (end - begin)) - 1); }
       if (is_bits_reverse) { value = bits_reverse(value, end - begin); }
       return value;
    }

    uint64_t bit_vector::bits_read_from_two_cells(uint64_t begin, uint64_t end, bool is_bits_reverse) const {
        uint64_t value = (this->vec[begin / this->cell_size] >> (begin % this->cell_size))
            | (
                (this->vec[(end - 1) / this->cell_size] & ((1LL << (end % this->cell_size)) - 1))
                << (this->cell_size - (begin % this->cell_size))
            );

       if (is_bits_reverse) { value = bits_reverse(value, end - begin); }
       return value;
    }

    void bit_vector::bits_write_to_a_cell(uint64_t begin, uint64_t end, uint64_t value, bool is_bits_reverse) {
        if (is_bits_reverse) { value = bits_reverse(value, end - begin); }

        uint64_t mask = 0;
        if ((end - begin) < this->cell_size) { mask = 1LL << (end - begin); }
        this->vec[(end - 1) / this->cell_size] &= ~((mask - 1) << (begin % this->cell_size));
        this->vec[(end - 1) / this->cell_size] |= (value << (begin % this->cell_size));
    }

    void bit_vector::bits_write_to_two_cells(uint64_t begin, uint64_t end, uint64_t value, bool is_bits_reverse) {
        if (is_bits_reverse) { value = bits_reverse(value, end - begin); }

        this->vec[begin / this->cell_size] &= ((1LL << (begin % this->cell_size)) - 1);
        this->vec[begin / this->cell_size] |= (value << (begin % this->cell_size));
        this->vec[(end - 1) / this->cell_size] &= ~((1LL << (end % this->cell_size)) - 1);
        this->vec[(end - 1) / this->cell_size] |= (value >> (this->cell_size - (begin % this->cell_size)));
    }
}
