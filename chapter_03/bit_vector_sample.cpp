#include <iostream>
#include <numeric>
#include <vector>
#include "cds/bit_vector.h"


using namespace std;
using namespace cds;


int main(int argc, char **argv) {
    bit_vector bv;
    bv.resize(bv.cell_size * 3);
    bv.bit_set(0);
    bv.bit_set(bv.cell_size - 1);
    bv.bit_set(bv.cell_size + 1);
    bv.bit_set(bv.cell_size * 2 - 2);
    bv.bit_set(bv.cell_size * 2);
    bv.bit_set(bv.cell_size * 3 - 1);

    vector<int> range(bv.size);
    iota(range.begin(), range.end(), 0);
    for (auto i : range) {
        if (i % bv.cell_size == 0) cout << endl;
        cout << bv.bit_read(i);
    }
    cout << endl;
    return 0;
}
