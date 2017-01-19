#include <vector>
#include "bit_vector.h"


namespace cds {
    class sampled_pointers {
    public:
        bit_vector bv;
        std::vector<unsigned int> samples;
        unsigned int rate;
        unsigned int size;

        sampled_pointers(unsigned int rate = 4);

        unsigned int read(unsigned int index);
        void push_back(unsigned int value);
        unsigned int bits_reverse(unsigned int value, unsigned int length);
    };
}
