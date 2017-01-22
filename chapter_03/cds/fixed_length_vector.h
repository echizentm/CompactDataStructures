#include "bit_vector.h"


namespace cds {
    class fixed_length_vector {
        bit_vector bv;
        unsigned int elements_in_a_cell;
        unsigned int rest_size_of_a_cell;

        unsigned int get_bit_index(unsigned int index);

    public:
        unsigned int length;
        unsigned int size;
        bool is_rapid;

        fixed_length_vector(unsigned int length, unsigned int size = 0, bool is_rapid = false);

        void resize(unsigned int size);
        unsigned int vector_size();
        unsigned int read(unsigned int index);
        void write(unsigned int index, unsigned int value);
    };
}
