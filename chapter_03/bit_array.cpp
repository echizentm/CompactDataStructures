#include <iostream>
#include <vector>


using namespace std;


class bit_array {
    const unsigned int BITS_OF_BYTE = 8;
    vector<unsigned int> vec;

    void push_to_index(unsigned int index) {
        while (vec.size() <= (index / cell_size)) {
            vec.push_back(0);
        }
    }

public:
    unsigned int cell_size = sizeof(unsigned int) * BITS_OF_BYTE;

    unsigned int bit_read(unsigned int index) {
        push_to_index(index);
        return vec[index / cell_size] >> (index % cell_size) & 1;
    }
    void bit_set(unsigned int index) {
        push_to_index(index);
        vec[index / cell_size] |= (1 << (index % cell_size));
    }
    void bit_clear(unsigned int index) {
        push_to_index(index);
        vec[index / cell_size] &= ~(1 << (index % cell_size));
    }
};


int main(int argc, char **argv) {
    bit_array a;
    a.bit_set(0);
    a.bit_set(a.cell_size - 1);
    a.bit_set(a.cell_size + 1);
    a.bit_set(a.cell_size * 2 - 2);
    a.bit_set(a.cell_size * 2);
    a.bit_set(a.cell_size * 3 - 1);

    for (int i = 0; i < a.cell_size * 3; i++) {
        cout << a.bit_read(i);
        if (i % a.cell_size == (a.cell_size - 1)) {
            cout << endl;
        }
    }
    return 0;
}
