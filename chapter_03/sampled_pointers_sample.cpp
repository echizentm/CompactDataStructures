#include <iostream>
#include <vector>
#include "cds/sampled_pointers.h"


using namespace std;
using namespace cds;


int main(int argc, char **argv) {
    sampled_pointers sp;
    vector<int> numbers = {0, 1, 0, 2, 5, 1, 3, 2, 8, 2};

    for (auto number : numbers) {
        sp.push_back(number);
        cout << number << " ";
    }
    cout << endl;

    for (int i = 0; i < sp.bv.size; i++) {
        cout << sp.bv.bit_read(i) << " ";
    }
    cout << endl;

    for (auto sample : sp.samples) {
        cout << sample << " ";
    }
    cout << endl;

    for (int i = 0; i < sp.size; i++) {
        cout << sp.read(i) << " ";
    }
    cout << endl;

    return 0;
}
