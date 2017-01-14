#include <vector>


namespace cds {
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

        bool is_in_a_cell(unsigned int begin, unsigned int end);
        unsigned int bits_read_from_a_cell(unsigned int begin, unsigned int end);
        unsigned int bits_read_from_two_cells(unsigned int begin, unsigned int end);
        void bits_write_to_a_cell(unsigned int begin, unsigned int end, unsigned int value);
        void bits_write_to_two_cells(unsigned int begin, unsigned int end, unsigned int value);
    };
}
