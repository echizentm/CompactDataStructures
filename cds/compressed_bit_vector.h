#pragma once
#include <vector>
#include <map>
#include "bit_vector.h"


namespace cds {
    class compressed_bit_vector {
    protected:
        std::vector<std::vector<uint64_t> > combinations;
        std::vector<uint64_t> offset_bits;
        std::vector<uint64_t> offset_samples;
        std::vector<uint8_t> classes;
        bit_vector offsets;

        void compute_combinations(uint64_t block_size);

        std::pair<uint64_t, uint64_t> encode(const bit_vector &bv, uint64_t begin, uint64_t end) const;
        uint64_t decode(uint64_t cclass, uint64_t offset, uint64_t index, bool is_rank = false) const;

    public:
        const uint64_t block_size = sizeof(uint64_t) * 8 - 1;
        const uint64_t sampling_rate = sizeof(uint64_t) * 8 - 1;
        uint64_t size;

        compressed_bit_vector(const bit_vector& bv);

        uint64_t vector_size() const;
        uint64_t access(uint64_t index) const;
    };
}
