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
        return 0;
    }

    void direct_access_codes::write(unsigned int index, unsigned int value) {

    }
}
