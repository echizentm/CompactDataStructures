#include <algorithm>
#include "partial_sums.h"


namespace cds {
    using namespace std;

    partial_sums::partial_sums(uint64_t length, uint64_t rate, uint64_t size, bool is_rapid)
    : fixed_length_vector(length, size, is_rapid) {
        this->rate = rate;
        this->resize(size);
    }


    void partial_sums::resize(uint64_t size) {
        fixed_length_vector::resize(size);
        this->samples.resize(
            (size + this->rate - 2) / this->rate + 1,
            (this->samples.size() > 0) ? *(this->samples.rbegin()) : 0
        );
    }

    uint64_t partial_sums::vector_size() const {
        return fixed_length_vector::vector_size() + this->samples.size();
    }

    void partial_sums::write(uint64_t index, uint64_t value) {
        uint64_t pos = (index + this->rate - 1)  / this->rate;
        while (pos < this->samples.size()) {
            this->samples[pos] += (value - this->read(index));
            pos++;
        }
        fixed_length_vector::write(index, value);
    }


    uint64_t partial_sums::sum(uint64_t index) const {
        uint64_t pos = index / this->rate;
        uint64_t sum = this->samples[pos];
        pos = pos * this->rate + 1;
        while (pos <= index) {
            sum += this->read(pos);
            pos++;
        }
        return sum;
    }

    uint64_t partial_sums::search(uint64_t value) const {
        if (value <= *(this->samples.begin())) {
            return 0;
        }

        vector<uint64_t>::const_iterator it = lower_bound(
            this->samples.begin(), this->samples.end(), value
        );
        it--;

        uint64_t sum = *it;
        uint64_t pos = distance(this->samples.begin(), it) * this->rate;
        while (sum < value && pos < this->size) {
            pos++;
            sum += this->read(pos);
        }
        return pos;
    }
}
