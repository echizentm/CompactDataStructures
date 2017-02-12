#include <iostream>
#include <vector>
#include "sampled_pointers.h"
#include "dense_pointers.h"
#include "direct_access_codes.h"
#include "elias_fano_codes.h"


using namespace std;
using namespace cds;


int main(int argc, char **argv) {
    vector<int> numbers = {0, 1, 0, 2, 5, 1, 3, 2, 8, 2};
    sampled_pointers sp;
    dense_pointers dp(3);
    direct_access_codes dac(2);
    elias_fano_codes efc;

    for (int i = 0; i < numbers.size(); i++) {
        sp.push_back(numbers[i]);
        dp.push_back(numbers[i]);
        dac.push_back(numbers[i]);
        efc.push_back(numbers[i]);
        cout << numbers[i] << " ";
    }
    cout << endl;

    cout << "sampled pointers: ";
    for (int i = 0; i < sp.size; i++) {
        cout << sp.read(i) << " ";
    }
    cout << endl;
    cout << "vector size: " << sp.vector_size() << endl;

    cout << "dense pointers: ";
    for (int i = 0; i < dp.size; i++) {
        cout << dp.read(i) << " ";
    }
    cout << endl;
    cout << "vector size: " << dp.vector_size() << endl;

    cout << "direct access codes: ";
    for (int i = 0; i < dac.size; i++) {
        cout << dac.read(i) << " ";
    }
    cout << endl;
    cout << "vector size: " << dac.vector_size() << endl;

    cout << "elias fano codes: ";
    for (int i = 0; i < efc.size; i++) {
        cout << efc.read(i) << " ";
    }
    cout << endl;
    cout << "vector size: " << efc.vector_size() << endl;
    return 0;
}
