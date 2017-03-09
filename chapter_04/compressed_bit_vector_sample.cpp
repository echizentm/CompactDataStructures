#include <iostream>
#include <cmath>
#include "bit_vector.h"
#include "compressed_bit_vector.h"


using namespace std;
using namespace cds;


int main(int argc, char **argv) {
    compressed_bit_vector cbv(8);
    int upper_bound = pow(2, cbv.block_size);

    bit_vector bv(upper_bound * cbv.block_size);
    for (int i = 0; i < upper_bound; i++) {
        bv.bits_write(i * cbv.block_size, (i + 1) * cbv.block_size, i, true);
    }

    for (int i = 0; i < upper_bound; i++) {
        pair<unsigned int, unsigned int> enc = cbv.encode(bv, i * cbv.block_size, (i + 1) * cbv.block_size);
        int decoded = cbv.decode(enc.first, enc.second).bits_read(0, cbv.block_size, true);

        cout << "i: " << i << " class: " << enc.first << " offset: " << enc.second
             << " decoded: " << decoded << endl;
        if (decoded != i) {
            cout << "failure!" << endl;
        }
    }
    return 0;
}
