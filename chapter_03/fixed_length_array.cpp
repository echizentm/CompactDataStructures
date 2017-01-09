#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>


using namespace std;
using namespace std::chrono;


class fixed_length_array {
    unsigned int length;
    unsigned int size;
    vector<unsigned int> vec;

    void push_to_index(unsigned int index) {
        while (vec.size() <= (index / cell_size)) {
            vec.push_back(0);
        }
    }
    bool is_in_a_cell(unsigned int begin, unsigned int end) {
        return ((begin / cell_size) == ((end - 1) / cell_size));
    }
    unsigned int bits_read_from_a_cell(unsigned int begin, unsigned int end) {
        return vec[(end - 1) / cell_size]
               >> (begin % cell_size)
               & ((1 << (end - begin)) - 1);
    }
    unsigned int bits_read_from_two_cells(unsigned int begin, unsigned int end) {
        return (vec[begin / cell_size] >> (begin % cell_size))
               | (
                   (vec[(end - 1) / cell_size] & ((1 << (end % cell_size)) - 1))
                   << (cell_size - (begin % cell_size))
               );
    }
    void bits_write_to_a_cell(unsigned int begin, unsigned int end, unsigned int value) {
        vec[(end - 1) / cell_size] &= ~(
            ((1 << (end - begin)) - 1)
            << (begin % cell_size)
        );
        vec[(end - 1) / cell_size] |= (value << (begin % cell_size));
    }
    void bits_write_to_two_cells(unsigned int begin, unsigned int end, unsigned int value) {
        vec[begin / cell_size] &= (
            (1 << (begin % cell_size)) - 1
        );
        vec[begin / cell_size] |= (
            value << (begin % cell_size)
        );
        vec[(end - 1) / cell_size] &= ~(
            (1 << (end % cell_size)) - 1
        );
        vec[(end - 1) / cell_size] |= (
            value >> (cell_size - (begin % cell_size))
        );
    }
    unsigned int bits_read(unsigned int begin, unsigned int end) {
        if (is_in_a_cell(begin, end)) {
            return bits_read_from_a_cell(begin, end);
        } else {
            return bits_read_from_two_cells(begin, end);
        }
    }
    void bits_write(unsigned int begin, unsigned int end, unsigned int value) {
        if (is_in_a_cell(begin, end)) {
            bits_write_to_a_cell(begin, end, value);
        } else {
            bits_write_to_two_cells(begin, end, value);
        }
    }

public:
    const unsigned int cell_size = sizeof(unsigned int) * 8;

    fixed_length_array(unsigned int length) {
        this->length = length;
        this->size = 0;
    }
    unsigned int read(unsigned int index) {
        return bits_read(index * length, (index + 1) * length);
    }
    void write(unsigned int index, unsigned int value) {
        bits_write(index * length, (index + 1) * length, value);
    }
    void push_back(unsigned int value) {
        push_to_index((size + 1) * length - 1);
        write(size, value);
        size++;
    }
    unsigned int vector_size() {
        return vec.size();
    }
};


bool run_vector(int length, int num) {
    vector<unsigned int> vec;
    vector<int> range(num);
    iota(range.begin(), range.end(), 0);
    int mod = pow(2, length);

    cout << "run vector (length = " << length << ")" << endl;
    auto begin_write = system_clock::now();
    for (auto i : range) { vec.push_back(i % mod); }
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


bool run_fixed_length_array(int length, int num) {
    fixed_length_array a(length);
    vector<int> range(num);
    iota(range.begin(), range.end(), 0);
    int mod = pow(2, length);

    cout << "run fixed length array (length = " << length << ")" << endl;
    auto begin_write = system_clock::now();
    for (auto i : range) { a.push_back(i % mod); }
    auto end_write = system_clock::now();
    cout << "msec to write: " << duration_cast<milliseconds>(end_write - begin_write).count() << endl;

    int count = 0;
    auto begin_read = system_clock::now();
    for (auto i : range) { if (a.read(i) == (i % mod)) { count++; }; }
    auto end_read = system_clock::now();
    cout << "size of vector: " << a.vector_size() << endl;
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
        if (!run_fixed_length_array(length, num)) { cout << "failure!" << endl; return 1; }
    }
    return 0;
}
