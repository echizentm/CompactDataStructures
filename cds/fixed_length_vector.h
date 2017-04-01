#pragma once
#include "bit_vector.h"


namespace cds {
    class fixed_length_vector {
        bit_vector bv;
        uint64_t elements_in_a_cell;
        uint64_t rest_size_of_a_cell;

        uint64_t get_bit_index(uint64_t index) const;

    public:
        uint64_t length;
        uint64_t size;
        bool is_rapid;

        fixed_length_vector(uint64_t length, uint64_t size = 0, bool is_rapid = false);

        void resize(uint64_t size);
        uint64_t vector_size() const;
        uint64_t read(uint64_t index) const;
        void write(uint64_t index, uint64_t value);
    };
}
