#include <algorithm>
#include "bit_vector_rank.h"


namespace cds {
    using namespace std;

    uint64_t popcount(uint64_t bits) {
        uint64_t count = 0;
        while (bits) {
            bits &= bits - 1;
            count++;
        }
        return count;
    }

    void bit_vector_rank::bit_write(uint64_t index, bool is_set) {
        if (index >= this->size) { this->resize(index + 1); }

        if (bit_read(index) == (is_set ? 1 : 0)) { return; }

        bit_vector::bit_set(index);

        uint64_t sample_index = index / (this->rate * this->cell_size) + 1;
        uint64_t cell_index = this->rate * (sample_index - 1);
        uint64_t cell_end = min(uint64_t(this->cell_ranks.size()), this->rate * sample_index);

        while (sample_index < this->sample_ranks.size()) {
            this->sample_ranks[sample_index] += (is_set ? 1 : -1);
            sample_index++;
        }
        this->cell_ranks[cell_index] = 0;
        while ((cell_index + 1) < cell_end) {
            this->cell_ranks[cell_index + 1] = this->cell_ranks[cell_index] + popcount(this->vec[cell_index]);
            cell_index++;
        }
    }


    bit_vector_rank::bit_vector_rank(uint64_t rate, uint64_t size) {
        this->rate = rate;
        this->resize(size);
    }

    void bit_vector_rank::resize(uint64_t size) {
        bit_vector::resize(size);
        if (size == 0) {
            this->sample_ranks.resize(1, 0);
            this->cell_ranks.resize(1, 0);
        } else {
            this->sample_ranks.resize(((size - 1) / (this->rate * this->cell_size)) + 2, *(this->sample_ranks.rbegin()));
            this->cell_ranks.resize(((size - 1) / this->cell_size) + 1, 0);
        }
    }

    uint64_t bit_vector_rank::vector_size() const {
        return bit_vector::vector_size() + this->sample_ranks.size() +
               this->cell_ranks.size() * sizeof(uint16_t) / sizeof(uint64_t);
    }

    void bit_vector_rank::bit_set(uint64_t index) {
        this->bit_write(index, true);
    }

    void bit_vector_rank::bit_clear(uint64_t index) {
        this->bit_write(index, false);
    }

    uint64_t bit_vector_rank::rank(uint64_t index) const {
        uint64_t sample_index = index / (this->rate * this->cell_size);
        uint64_t cell_index = index / this->cell_size;

        return this->sample_ranks[sample_index] +
               this->cell_ranks[cell_index] +
               popcount(this->bits_read(cell_index * this->cell_size, index + 1));
    }

    uint64_t bit_vector_rank::rank_naive(uint64_t index) const {
        uint64_t rank = 0;
        for (uint64_t i = 0; i <= index; i++) {
            rank += this->bit_read(i);
        }
        return rank;
    }
};
