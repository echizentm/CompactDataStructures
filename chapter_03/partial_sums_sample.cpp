#include <iostream>
#include <cmath>
#include "partial_sums.h"


using namespace std;
using namespace cds;


int main(int argc, char **argv) {
    int same_value_size = 8;
    partial_sums ps(
        ceil(log2(10 * same_value_size)),
        4,
        10 * same_value_size
    );

    cout << "write: ";
    for (int i = 0; i < ps.size; i+=same_value_size) {
        ps.write(i, i / same_value_size);
        cout << i / same_value_size << " ";
        for (int j = 0; j < (same_value_size - 1); j++) {
            ps.write(i + 1, 0);
            cout << 0 << " ";
        }
    }
    cout << endl;

    cout << "read: ";
    for (int i = 0; i < ps.size; i++) {
        cout << ps.read(i) << " ";
    }
    cout << endl;

    cout << "samples: ";
    for (int i = 0; i < ps.samples.size(); i++) {
        cout << ps.samples[i] << " ";
    }
    cout << endl;

    cout << "sum: ";
    for (int i = 0; i < ps.size; i++) {
        cout << ps.sum(i) << " ";
    }
    cout << endl;

    cout << "search: ";
    int j = 0;
    cout << endl << ps.sum(j) << ": ";
    for (int i = 0; i <= ps.sum(ps.size - 1); i++) {
        if (i > ps.sum(j)) {
            j+=same_value_size;
            cout << endl << ps.sum(j) << ": ";
        }
        cout << ps.search(i) << " ";
    }
    cout << endl << "  : " << ps.search(ps.sum(ps.size - 1) + 1) << endl;
    return 0;
}
