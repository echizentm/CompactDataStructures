#include "direct_access_codes.h"


namespace cds {
    direct_access_codes::direct_access_codes(
        unsigned int length, unsigned int size
    ) {
        this->length = length;
        this->markers.push_back(partial_sums(1));
        this->blocks.push_back(fixed_length_vector(this->length));
        this->resize(size);
    }

    void direct_access_codes::resize(unsigned int size) {
        this->size = size;
        this->markers.begin()->resize(size);
        this->blocks.begin()->resize(size);
    }

    unsigned int direct_access_codes::vector_size() {
        unsigned int vector_size = 0;
        for (auto marker : this->markers) {
            vector_size += marker.vector_size();
        }
        for (auto block : this->blocks) {
            vector_size += block.vector_size();
        }
        return vector_size;
    }

    unsigned int direct_access_codes::read(unsigned int index) {
        unsigned int value = 0;
        unsigned int depth = 0;
        while (1) {
            value |= (this->blocks[depth].read(index) << (depth * this->length));
            if (this->markers[depth].read(index) == 0) {
                return value;
            }
            index = this->markers[depth].sum(index) - 1;
            depth++;
        }
    }

    void direct_access_codes::write(unsigned int index, unsigned int value) {
        unsigned int mask = 0;
        for (unsigned int i = 0; i < this->length; i++) {
            mask = (mask << 1) | 1;
        }

        unsigned int depth = 0;
        while (1) {
            if (this->markers.size() == depth) {
                this->markers.push_back(partial_sums(1));
            }
            if (this->blocks.size() == depth) {
                this->blocks.push_back(fixed_length_vector(this->length));
            }
            if (this->markers[depth].size < (index + 1)) {
                this->markers[depth].resize(index + 1);
            }
            if (this->blocks[depth].size < (index + 1)) {
                this->blocks[depth].resize(index + 1);
            }

            this->blocks[depth].write(index, value & mask);
            value >>= this->length;
            if (value) { 
                this->markers[depth].write(index, 1);
            } else {
                break;
            }
            index = this->markers[depth].sum(index) - 1;
            depth++;
        }
    }
}
