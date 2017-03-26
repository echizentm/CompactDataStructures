#pragma once
#include <vector>


namespace cds {
    uint64_t bits_reverse(uint64_t value, uint64_t length);
    uint64_t bits_length(uint64_t value);

    class bit_vector {
    public:
        std::vector<uint64_t> vec;

    public:
        const uint64_t cell_size = sizeof(uint64_t) * 8;
        uint64_t size;

        bit_vector(uint64_t size = 0);

        void resize(uint64_t size);
        uint64_t vector_size();
        uint64_t bit_read(uint64_t index) const;
        void bit_set(uint64_t index);
        void bit_clear(uint64_t index);

        uint64_t bits_read(uint64_t begin, uint64_t end, bool bits_reverse = false);
        void bits_write(uint64_t begin, uint64_t end, uint64_t value, bool bits_reverse = false);

        bool is_in_a_cell(uint64_t begin, uint64_t end);
        uint64_t bits_read_from_a_cell(uint64_t begin, uint64_t end, bool bits_reverse = false);
        uint64_t bits_read_from_two_cells(uint64_t begin, uint64_t end, bool bits_reverse = false);
        void bits_write_to_a_cell(uint64_t begin, uint64_t end, uint64_t value, bool bits_reverse = false);
        void bits_write_to_two_cells(uint64_t begin, uint64_t end, uint64_t value, bool bits_reverse = false);
    };
}
