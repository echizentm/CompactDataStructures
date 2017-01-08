#include <iostream>
#include <vector>


using namespace std;


class fixed_length_array {
    const unsigned int BITS_OF_BYTE = 8;
    vector<unsigned int> vec;

    void push_to_index(unsigned int index) {
        while (vec.size() <= (index / cell_size)) {
            vec.push_back(0);
        }
    }
    bool is_in_a_cell(unsigned int begin, unsigned int end) {
        return ((begin / cell_size) == (end / cell_size));
    }
    unsigned int bits_read_from_a_cell(unsigned int begin, unsigned int end) {
        return vec[end / cell_size]
               >> (begin % cell_size)
               & ((1 << (end - begin + 1)) - 1);
    }
    unsigned int bits_read_from_two_cells(unsigned int begin, unsigned int end) {
        return (vec[begin / cell_size] >> (begin % cell_size))
               | (
                   (vec[end / cell_size] & ((1 << ((end + 1) % cell_size)) - 1))
                   << (cell_size - (begin % cell_size))
               );
    }
    void bits_write_to_a_cell(unsigned int begin, unsigned int end, unsigned int value) {
        vec[end / cell_size] &= ~(
            ((1 << (end - begin + 1)) - 1)
            << (begin % cell_size)
        );
        vec[end / cell_size] |= (value << (begin % cell_size));
    }
    void bits_write_to_two_cells(unsigned int begin, unsigned int end, unsigned int value) {
        vec[begin / cell_size] &= (
            (1 << (begin % cell_size)) - 1
        );
        vec[begin / cell_size] |= (
            value << (begin % cell_size)
        );
        vec[end / cell_size] &= ~(
            (1 << ((end + 1) % cell_size)) - 1
        );
        vec[end / cell_size] |= (
            value >> (cell_size - (begin % cell_size))
        );
    }
    unsigned int bits_read(unsigned int begin, unsigned int end) {
        push_to_index(end);
        if (is_in_a_cell(begin, end)) {
            return bits_read_from_a_cell(begin, end);
        } else {
            return bits_read_from_two_cells(begin, end);
        }
    }
    void bits_write(unsigned int begin, unsigned int end, unsigned int value) {
        push_to_index(end);
        if (is_in_a_cell(begin, end)) {
            bits_write_to_a_cell(begin, end, value);
        } else {
            bits_write_to_two_cells(begin, end, value);
        }
    }

public:
    unsigned int cell_size = sizeof(unsigned int) * BITS_OF_BYTE;
    unsigned int length;

    fixed_length_array(unsigned int length) {
        this->length = length;
    }
    unsigned int read(unsigned int index) {
        return bits_read(index * length, (index + 1) * length - 1);
    }
    void write(unsigned int index, unsigned int value) {
        bits_write(index * length, (index + 1) * length - 1, value);
    }
    unsigned int vector_size() {
        return vec.size();
    }
};


int main(int argc, char **argv) {
    fixed_length_array a(5);

    cout << "vector size = " << a.vector_size() << endl;
    for (int i = 0; i < 31; i++) {
        a.write(i, 31 - i);
    }
    cout << endl;

    cout << "vector size = " << a.vector_size() << endl;
    for (int i = 0; i < 31; i++) {
        cout << a.read(i) << ' ';
    }
    cout << endl;
    return 0;
}
