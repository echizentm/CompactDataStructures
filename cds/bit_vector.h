#pragma once
#include <vector>


namespace cds {
    unsigned int bits_reverse(unsigned int value, unsigned int length);
    unsigned int bits_length(unsigned int value);

    class bit_vector {
        std::vector<unsigned int> vec;

    public:
        const unsigned int cell_size = sizeof(unsigned int) * 8;
        unsigned int size;

        bit_vector(unsigned int size = 0);

        void resize(unsigned int size);
        unsigned int vector_size();
        unsigned int bit_read(unsigned int index);
        void bit_set(unsigned int index);
        void bit_clear(unsigned int index);

        unsigned int bits_read(unsigned int begin, unsigned int end, bool bits_reverse = false);
        void bits_write(unsigned int begin, unsigned int end, unsigned int value, bool bits_reverse = false);

        bool is_in_a_cell(unsigned int begin, unsigned int end);
        unsigned int bits_read_from_a_cell(unsigned int begin, unsigned int end, bool bits_reverse = false);
        unsigned int bits_read_from_two_cells(unsigned int begin, unsigned int end, bool bits_reverse = false);
        void bits_write_to_a_cell(unsigned int begin, unsigned int end, unsigned int value, bool bits_reverse = false);
        void bits_write_to_two_cells(unsigned int begin, unsigned int end, unsigned int value, bool bits_reverse = false);
    };
}
