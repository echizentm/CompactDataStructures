#include "fixed_length_vector.h"


namespace cds {
    uint64_t fixed_length_vector::get_bit_index(uint64_t index) const {
        return (
            (this->is_rapid && this->rest_size_of_a_cell > 0) ?
            index / this->elements_in_a_cell * this->bv.cell_size + index % this->elements_in_a_cell * this->length :
            index * this->length
        );
    }

    fixed_length_vector::fixed_length_vector(uint64_t length, uint64_t size, bool is_rapid) {
        this->length = length;
        this->is_rapid = is_rapid;
        this->elements_in_a_cell = bv.cell_size / this->length;
        this->rest_size_of_a_cell = bv.cell_size % this->length;
        resize(size);
    }

    void fixed_length_vector::resize(uint64_t size) {
        this->size = size;
        this->bv.resize(this->get_bit_index(this->size));
    }

    uint64_t fixed_length_vector::vector_size() const {
        return this->bv.vector_size();
    }

    uint64_t fixed_length_vector::read(uint64_t index) const {
        uint64_t bit_index = this->get_bit_index(index);

        if (this->is_rapid || this->rest_size_of_a_cell == 0) {
            return this->bv.bits_read_from_a_cell(bit_index, bit_index + this->length);
        } else {
            return this->bv.bits_read(bit_index, bit_index + this->length);
        }
    }

    void fixed_length_vector::write(uint64_t index, uint64_t value) {
        uint64_t bit_index = this->get_bit_index(index);

        if (this->is_rapid || this->rest_size_of_a_cell == 0) {
            this->bv.bits_write_to_a_cell(bit_index, bit_index + this->length, value);
        } else {
            this->bv.bits_write(bit_index, bit_index + this->length, value);
        }
    }
}
