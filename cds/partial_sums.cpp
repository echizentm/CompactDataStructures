#include <algorithm>
#include "partial_sums.h"


namespace cds {
    using namespace std;

    partial_sums::partial_sums(
        unsigned int length,
        unsigned int rate,
        unsigned int size,
        bool is_rapid
    ) : fixed_length_vector(length, size, is_rapid) {
        this->rate = rate;
        this->samples.resize((this->size + this->rate - 1) / this->rate);
    }


    void partial_sums::resize(unsigned int size) {
        fixed_length_vector::resize(size);
        this->samples.resize((size + this->rate - 1) / this->rate);
    }

    unsigned int partial_sums::vector_size() {
        return fixed_length_vector::vector_size() + this->samples.size();
    }

    void partial_sums::write(unsigned int index, unsigned int value) {
        unsigned int pos = (index + this->rate - 1)  / this->rate;
        while (pos < this->samples.size()) {
            this->samples[pos] += (value - this->read(index));
            pos++;
        }
        fixed_length_vector::write(index, value);
    }


    unsigned int partial_sums::sum(unsigned int index) {
        unsigned int pos = index / this->rate;
        unsigned int sum = this->samples[pos];
        pos = pos * this->rate + 1;
        while (pos <= index) {
            sum += this->read(pos);
            pos++;
        }
        return sum;
    }

    unsigned int partial_sums::search(unsigned int value) {
        vector<unsigned int>::iterator it = upper_bound(
            this->samples.begin(), this->samples.end(), value
        );
        it--;

        unsigned int sum = *it;
        unsigned int pos = distance(this->samples.begin(), it) * this->rate;
        if (sum == value) {
            while (this->read(pos) == 0 && pos > 0) {
                pos--;
            }
            return pos;
        } else {
            while (sum < value && pos < this->size) {
                pos++;
                sum += this->read(pos);
            }
            return pos;
        }
    }
}