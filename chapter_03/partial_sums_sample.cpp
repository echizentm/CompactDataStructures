#include <iostream>
#include <cmath>
#include "partial_sums.h"


using namespace std;
using namespace cds;


int main(int argc, char **argv) {
    int same_value_size = 2;
    partial_sums ps(ceil(log2(10 * same_value_size)), 4, 0);

    cout << "write: ";
    for (int i = 0; i < 10 * same_value_size; i+=same_value_size) {
        ps.resize(i + 1);
        ps.write(i, i / same_value_size);
        cout << i / same_value_size << " ";
        for (int j = 1; j < same_value_size; j++) {
            ps.resize(i + j + 1);
            ps.write(i + j, 0);
            cout << 0 << " ";
        }
    }
    cout << endl;

    cout << "read: ";
    for (int i = 0; i < ps.size; i++) {
        cout << ps.read(i) << " ";
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
