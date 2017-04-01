#include "bit_vector_rank.h"


namespace cds {
    uint64_t popcount(uint64_t bits) {
        uint64_t count = 0;
        while (bits) {
            bits &= bits - 1;
            count++;
        }
        return count;
    }


    bit_vector_rank::bit_vector_rank(uint64_t rate, uint64_t size)
    : bit_vector(size) {
        this->rate = rate;
        this->resize(size);
    }

    void bit_vector_rank::resize(uint64_t size) {
        bit_vector::resize(size);
        this->samples.resize(
            size / (this->rate * this->cell_size) + 2,
            (this->samples.size() > 0) ? *(this->samples.rbegin()) : 0
        );
    }

    uint64_t bit_vector_rank::vector_size() const {
        return bit_vector::vector_size() + this->samples.size();
    }

    void bit_vector_rank::bit_set(uint64_t index) {
        if (bit_read(index) == 1) { return; }
        uint64_t pos = index / (this->rate * this->cell_size) + 1;
        while (pos < this->samples.size()) {
            this->samples[pos]++;
            pos++;
        }
        bit_vector::bit_set(index);
    }

    void bit_vector_rank::bit_clear(uint64_t index) {
        if (bit_read(index) == 0) { return; }
        uint64_t pos = index / (this->rate * this->cell_size) + 1;
        while (pos < this->samples.size()) {
            this->samples[pos]--;
            pos++;
        }
        bit_vector::bit_clear(index);
    }

    uint64_t bit_vector_rank::rank(uint64_t index) const {
        uint64_t sample_index = index / (this->rate * this->cell_size);
        uint64_t cell_index = index / this->cell_size;

        uint64_t rank = this->samples[sample_index];
        for (uint64_t i = sample_index * this->rate; i < cell_index; i++) {
            rank += popcount(this->vec[i]);
        }
        return rank + popcount(this->bits_read(cell_index * this->cell_size, index + 1));
    }

    uint64_t bit_vector_rank::rank_naive(uint64_t index) const {
        uint64_t rank = 0;
        for (uint64_t i = 0; i <= index; i++) {
            rank += this->bit_read(i);
        }
        return rank;
    }
};
