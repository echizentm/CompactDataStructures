#include <chrono>
#include <iostream>
#include "compressed_bit_vector.h"


using namespace std;
using namespace std::chrono;
using namespace cds;


int main(int argc, char **argv) {
    int max = 1000;
    bit_vector bv((1 + max) * max / 2 + max);
    int sum = 0;
    for (int i = 0; i < max; i++) {
        sum += i;
        bv.bit_set(sum);
        sum++;
        bv.bit_set(sum);
    }

    compressed_bit_vector cbv(bv);


    cout << "size of 1s: " << max * 2 << endl;
    cout << "size of 0s: " << bv.size - max * 2 << endl;
    cout << endl;


    cout << "validate access" << endl;
    for (int i = 0; i < cbv.size; i++) {
        if (cbv.access(i) != bv.bit_read(i)) {
            cout << "failure." << endl;
            return 1;
        }
    } 
    cout << "success." << endl;
    cout << endl;


    cout << "vector_size(naive): " << bv.vector_size() << endl;
    cout << "vector_size(compressed): " << cbv.vector_size() << endl;
    cout << endl;


    auto begin_read = system_clock::now();
    for (int i = 0; i < bv.size; i++) { bv.bit_read(i); }
    auto end_read = system_clock::now();
    cout << "access time(msec)(naive): " << duration_cast<milliseconds>(end_read - begin_read).count() << endl;

    begin_read = system_clock::now();
    for (int i = 0; i < cbv.size; i++) { cbv.access(i); }
    end_read = system_clock::now();
    cout << "access time(msec)(compressed): " << duration_cast<milliseconds>(end_read - begin_read).count() << endl;
    return 0;
}
