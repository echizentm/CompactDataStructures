#include <iostream>
#include "bit_vector.h"
#include "compressed_bit_vector.h"


using namespace std;
using namespace cds;


int main(int argc, char **argv) {
    compressed_bit_vector cbv;
    int size = 4;
    cbv.compute_combinations(size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j <= i; j++) {
            cout << i << "C" << j << ": " << cbv.combinations[i][j] << endl;
        }
    }

    bit_vector bv(2 * size);
    bv.bit_set(1);
    bv.bit_set(4);
    bv.bit_set(6);
    bv.bit_set(7);
    pair<unsigned int, unsigned int> enc = cbv.encode(bv, 0, size);
    pair<unsigned int, unsigned int> enc2 = cbv.encode(bv, size, 2 * size);
    for (int i = 0; i < size; i++) {
        cout << bv.bit_read(i) << " ";
    }
    cout << endl;
    cout << "class: " << enc.first << " offset: " << enc.second << endl;

    for (int i = size; i < 2 * size; i++) {
        cout << bv.bit_read(i) << " ";
    }
    cout << endl;
    cout << "class: " << enc2.first << " offset: " << enc2.second << endl;
    return 0;
}
