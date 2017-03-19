#include <iostream>
#include "compressed_bit_vector.h"


using namespace std;
using namespace cds;


int main(int argc, char **argv) {
    int max = 100;
    bit_vector bv((1 + max) * max / 2);
    int sum = 0;
    for (int i = 0; i < max; i++) {
        sum += i;
        bv.bit_set(sum);
    }

    compressed_bit_vector cbv(bv);
    cout << "vector_size(naive): " << bv.vector_size() << endl;
    cout << "vector_size(compressed): " << cbv.vector_size() << endl;
    for (int i = 0; i < cbv.size; i++) {
        if (cbv.access(i) != bv.bit_read(i)) {
            cout << "failure." << endl;
            return 1;
        }
    } 
    cout << "success." << endl;
    return 0;
}
