#include <chrono>
#include <iostream>
#include "bit_vector_rank.h"


using namespace std;
using namespace std::chrono;
using namespace cds;


int main(int argc, char **argv) {
    bit_vector_rank bvr(4, 10000);

    for (int i = 0; i < bvr.size; i++) {
        if (i % 13 == 0) { bvr.bit_set(i); }
    }

    cout << "validate rank" << endl;
    for (int i = 0; i < 1000; i++) {
        if (bvr.rank(i) != bvr.rank_naive(i)) {
            cout << "failure." << endl;
            return 0;
        }
    }
    cout << "success." << endl;
    cout << endl;

    cout << "vector_size: " << bvr.vector_size() << endl;
    cout << endl;

    auto begin_read = system_clock::now();
    for (int i = 0; i < bvr.size; i++) { bvr.rank_naive(i); }
    auto end_read = system_clock::now();
    cout << "rank_naive time(msec): " << duration_cast<milliseconds>(end_read - begin_read).count() << endl;

    begin_read = system_clock::now();
    for (int i = 0; i < bvr.size; i++) { bvr.rank(i); }
    end_read = system_clock::now();
    cout << "rank time(msec): " << duration_cast<milliseconds>(end_read - begin_read).count() << endl;
    return 0;
}
