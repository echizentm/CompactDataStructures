#include <iostream>
#include "compressed_bit_vector.h"


using namespace std;
using namespace cds;


int main(int argc, char **argv) {
    compressed_bit_vector bv;
    int size = 4;
    bv.compute_combinations(size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j <= i; j++) {
            cout << i << "C" << j << ": " << bv.combinations[i][j] << endl;
        }
    }
    return 0;
}
