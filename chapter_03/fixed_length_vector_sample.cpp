#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>
#include "cds/bit_vector.h"


using namespace std;
using namespace std::chrono;
using namespace cds;


class fixed_length_vector {
    unsigned int length;
    unsigned int size;
    bit_vector bv;
    bool is_rapid;
    unsigned int cell_rest_size;
    unsigned int elements_in_a_cell;

    unsigned int get_bit_index(unsigned int index) {
        return (
            (is_rapid && cell_rest_size > 0) ?
            index / elements_in_a_cell * bv.cell_size + index % elements_in_a_cell * length :
            index * length
        );
    }
    unsigned int bits_read(unsigned int begin, unsigned int end) {
        if (is_rapid || bv.is_in_a_cell(begin, end)) {
            return bv.bits_read_from_a_cell(begin, end);
        } else {
            return bv.bits_read_from_two_cells(begin, end);
        }
    }
    void bits_write(unsigned int begin, unsigned int end, unsigned int value) {
        if (is_rapid || bv.is_in_a_cell(begin, end)) {
            bv.bits_write_to_a_cell(begin, end, value);
        } else {
            bv.bits_write_to_two_cells(begin, end, value);
        }
    }

public:
    fixed_length_vector(unsigned int length, unsigned int size = 0, bool is_rapid = false) {
        this->length = length;
        this->is_rapid = is_rapid;
        elements_in_a_cell = bv.cell_size / length;
        cell_rest_size = bv.cell_size % length;
        resize(size);
    }
    unsigned int read(unsigned int index) {
        unsigned int bit_index = get_bit_index(index);
        return bits_read(bit_index, bit_index + length);
    }
    void write(unsigned int index, unsigned int value) {
        unsigned int bit_index = get_bit_index(index);
        bits_write(bit_index, bit_index + length, value);
    }
    void resize(unsigned int size) {
        this->size = size;
        bv.resize(get_bit_index(size));
    }
    unsigned int vector_size() {
        return bv.vector_size();
    }
};


bool run_vector(int length, int num) {
    vector<unsigned int> vec(num);
    vector<int> range(num);
    iota(range.begin(), range.end(), 0);
    int mod = pow(2, length);

    cout << "run vector (length = " << length << ")" << endl;
    auto begin_write = system_clock::now();
    for (auto i : range) { vec[i] = i % mod; }
    auto end_write = system_clock::now();
    cout << "msec to write: " << duration_cast<milliseconds>(end_write - begin_write).count() << endl;

    int count = 0;
    auto begin_read = system_clock::now();
    for (auto i : range) { if (vec[i] == (i % mod)) { count++; }; }
    auto end_read = system_clock::now();
    cout << "size of vector: " << vec.size() << endl;
    cout << "rate of success: " << count << " / " << range.size() << endl;
    cout << "msec to read: " << duration_cast<milliseconds>(end_read - begin_read).count() << endl;
    cout << endl;
    return count == range.size();
}


bool run_fixed_length_vector(int length, int num, bool is_rapid) {
    fixed_length_vector vec(length, num, is_rapid);
    vector<int> range(num);
    iota(range.begin(), range.end(), 0);
    int mod = pow(2, length);

    cout << "run fixed length vec (length = " << length << ", is_rapid = " << is_rapid << ")" << endl;
    auto begin_write = system_clock::now();
    for (auto i : range) { vec.write(i, i % mod); }
    auto end_write = system_clock::now();
    cout << "msec to write: " << duration_cast<milliseconds>(end_write - begin_write).count() << endl;

    int count = 0;
    auto begin_read = system_clock::now();
    for (auto i : range) { if (vec.read(i) == (i % mod)) { count++; }; }
    auto end_read = system_clock::now();
    cout << "size of vector: " << vec.vector_size() << endl;
    cout << "rate of success: " << count << " / " << range.size() << endl;
    cout << "msec to read: " << duration_cast<milliseconds>(end_read - begin_read).count() << endl;
    cout << endl;
    return count == range.size();
}


int main(int argc, char **argv) {
    int num = 1000 * 1000;

    vector<int> range(sizeof(int) * 8 - 1);
    iota(range.begin(), range.end(), 1);
    for (auto length : range) {
        if (!run_vector(length, num)) { cout << "failure!" << endl; return 1; }
        if (!run_fixed_length_vector(length, num, true)) { cout << "failure!" << endl; return 1; }
        if (!run_fixed_length_vector(length, num, false)) { cout << "failure!" << endl; return 1; }
    }
    return 0;
}
