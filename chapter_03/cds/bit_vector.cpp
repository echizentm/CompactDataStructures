#include "bit_vector.h"


namespace cds {
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

    unsigned int bit_vector::bit_read(unsigned int index) {
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
        unsigned int begin, unsigned int end
    ) {
        if (this->is_in_a_cell(begin, end)) {
            return this->bits_read_from_a_cell(begin, end);
        } else {
            return this->bits_read_from_two_cells(begin, end);
        }
    }

    void bit_vector::bits_write(
        unsigned int begin, unsigned int end, unsigned int value
    ) {
        if (this->is_in_a_cell(begin, end)) {
            this->bits_write_to_a_cell(begin, end, value);
        } else {
            this->bits_write_to_two_cells(begin, end, value);
        }
    }


    bool bit_vector::is_in_a_cell(
        unsigned int begin, unsigned int end
    ) {
        return ((begin / this->cell_size) == ((end - 1) / this->cell_size));
    }

    unsigned int bit_vector::bits_read_from_a_cell(
        unsigned int begin, unsigned int end
    ) {
        return this->vec[(end - 1) / this->cell_size]
               >> (begin % this->cell_size)
               & ((1 << (end - begin)) - 1);
    }

    unsigned int bit_vector::bits_read_from_two_cells(
        unsigned int begin, unsigned int end
    ) {
        return (this->vec[begin / this->cell_size] >> (begin % this->cell_size))
               | (
                   (this->vec[(end - 1) / this->cell_size] & ((1 << (end % this->cell_size)) - 1))
                   << (this->cell_size - (begin % this->cell_size))
               );
    }

    void bit_vector::bits_write_to_a_cell(
        unsigned int begin, unsigned int end, unsigned int value
    ) {
        this->vec[(end - 1) / this->cell_size] &= ~(
            ((1 << (end - begin)) - 1)
            << (begin % this->cell_size)
        );
        this->vec[(end - 1) / this->cell_size] |= (value << (begin % this->cell_size));
    }

    void bit_vector::bits_write_to_two_cells(
        unsigned int begin, unsigned int end, unsigned int value
    ) {
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
