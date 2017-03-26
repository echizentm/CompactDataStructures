#include "direct_access_codes.h"


namespace cds {
    direct_access_codes::direct_access_codes(uint64_t length) {
        this->length = length;
        this->size   = 0;
        this->markers.push_back(partial_sums(1));
        this->blocks.push_back(fixed_length_vector(this->length));
    }

    uint64_t direct_access_codes::vector_size() {
        uint64_t vector_size = 0;
        for (auto marker : this->markers) {
            vector_size += marker.vector_size();
        }
        for (auto block : this->blocks) {
            vector_size += block.vector_size();
        }
        return vector_size;
    }

    uint64_t direct_access_codes::read(uint64_t index) {
        uint64_t value = 0;
        uint64_t depth = 0;
        while (1) {
            value |= (this->blocks[depth].read(index) << (depth * this->length));
            if (this->markers[depth].read(index) == 0) {
                return value;
            }
            index = this->markers[depth].sum(index) - 1;
            depth++;
        }
    }

    void direct_access_codes::push_back(uint64_t value) {
        uint64_t mask = 0;
        for (uint64_t i = 0; i < this->length; i++) {
            mask = (mask << 1) | 1;
        }

        uint64_t depth = 0;
        uint64_t index = this->size;
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
        this->size++;
    }
}
