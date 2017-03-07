#include "bit_vector.h"


namespace cds {
    unsigned int bits_reverse(unsigned int value, unsigned int length) {
        unsigned int reversed = 0;
        while (length > 0) {
            reversed <<= 1;
            reversed |= (value & 1);
            value >>= 1;
            length--;
        }
        return reversed;
    }

    unsigned int bits_length(unsigned int value) {
        unsigned int length = 0;
        while (value != 0) {
            value >>= 1;
            length++;
        }
        return length;
    }


    bit_vector::bit_vector(unsigned int size) {
        this->resize(size);
    }

    void bit_vector::resize(unsigned int size) {
        this->size = size;
        if (this->size > 0) {
            this->vec.resize((this->size - 1) / this->cell_size + 1);
        };
    }

    unsigned int bit_vector::vector_size() {
        return this->vec.size();
    }

    unsigned int bit_vector::bit_read(unsigned int index) const {
        return this->vec[index / this->cell_size]
               >> (index % this->cell_size) & 1;
    }

    void bit_vector::bit_set(unsigned int index) {
        this->vec[index / this->cell_size]
        |= (1 << (index % this->cell_size));
    }

    void bit_vector::bit_clear(unsigned int index) {
        this->vec[index / this->cell_size]
        &= ~(1 << (index % this->cell_size));
    }


    unsigned int bit_vector::bits_read(
        unsigned int begin, unsigned int end, bool is_bits_reverse
    ) {
        if (this->is_in_a_cell(begin, end)) {
            return this->bits_read_from_a_cell(begin, end, is_bits_reverse);
        } else {
            return this->bits_read_from_two_cells(begin, end, is_bits_reverse);
        }
    }

    void bit_vector::bits_write(
        unsigned int begin, unsigned int end, unsigned int value, bool is_bits_reverse
    ) {
        if (this->is_in_a_cell(begin, end)) {
            this->bits_write_to_a_cell(begin, end, value, is_bits_reverse);
        } else {
            this->bits_write_to_two_cells(begin, end, value, is_bits_reverse);
        }
    }


    bool bit_vector::is_in_a_cell(
        unsigned int begin, unsigned int end
    ) {
        return ((begin / this->cell_size) == ((end - 1) / this->cell_size));
    }

    unsigned int bit_vector::bits_read_from_a_cell(
        unsigned int begin, unsigned int end, bool is_bits_reverse
    ) {
       unsigned int value = this->vec[(end - 1) / this->cell_size]
                    >> (begin % this->cell_size)
                    & ((1 << (end - begin)) - 1);

       if (is_bits_reverse) {
           value = bits_reverse(value, end - begin);
       }
       return value;
    }

    unsigned int bit_vector::bits_read_from_two_cells(
        unsigned int begin, unsigned int end, bool is_bits_reverse
    ) {
        unsigned int value = (this->vec[begin / this->cell_size] >> (begin % this->cell_size))
                     | (
                         (this->vec[(end - 1) / this->cell_size] & ((1 << (end % this->cell_size)) - 1))
                         << (this->cell_size - (begin % this->cell_size))
                     );

       if (is_bits_reverse) {
           value = bits_reverse(value, end - begin);
       }
       return value;
    }

    void bit_vector::bits_write_to_a_cell(
        unsigned int begin, unsigned int end, unsigned int value, bool is_bits_reverse
    ) {
        if (is_bits_reverse) {
            value = bits_reverse(value, end - begin);
        }

        this->vec[(end - 1) / this->cell_size] &= ~(
            ((1 << (end - begin)) - 1)
            << (begin % this->cell_size)
        );
        this->vec[(end - 1) / this->cell_size] |= (value << (begin % this->cell_size));
    }

    void bit_vector::bits_write_to_two_cells(
        unsigned int begin, unsigned int end, unsigned int value, bool is_bits_reverse
    ) {
        if (is_bits_reverse) {
            value = bits_reverse(value, end - begin);
        }

        this->vec[begin / this->cell_size] &= (
            (1 << (begin % this->cell_size)) - 1
        );
        this->vec[begin / this->cell_size] |= (
            value << (begin % this->cell_size)
        );
        this->vec[(end - 1) / this->cell_size] &= ~(
            (1 << (end % this->cell_size)) - 1
        );
        this->vec[(end - 1) / this->cell_size] |= (
            value >> (this->cell_size - (begin % this->cell_size))
        );
    }
}
