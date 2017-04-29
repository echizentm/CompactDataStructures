#include <chrono>
#include <iostream>
#include "bit_vector_rank.h"
#include "compressed_bit_vector_rank.h"


using namespace std;
using namespace std::chrono;
using namespace cds;


int main(int argc, char **argv) {
    int size = 1000000;
    int bit_set_rate = 13;
    int validate_size = 1000;


    cout << "# bit vector #" << endl;
    bit_vector bv(size);

    for (int i = 0; i < size; i++) { if (i % bit_set_rate == 0) { bv.bit_set(i); } }

    cout << "vector size: " << bv.vector_size() << endl;

    auto begin_read = system_clock::now();
    for (int i = 0; i < bv.size; i++) { bv.bit_read(i); }
    auto end_read = system_clock::now();
    cout << "access time(msec): " << duration_cast<milliseconds>(end_read - begin_read).count() << endl;
    cout << endl;


    cout << "# compressed bit vector #" << endl;
    compressed_bit_vector cbv(bv);

    cout << "vector size: " << cbv.vector_size() << endl;

    begin_read = system_clock::now();
    for (int i = 0; i < cbv.size; i++) { cbv.access(i); }
    end_read = system_clock::now();
    cout << "access time(msec): " << duration_cast<milliseconds>(end_read - begin_read).count() << endl;
    cout << endl;


    cout << "# bit vector + rank #" << endl;
    bit_vector_rank bvr(63);

    for (int i = 0; i < size; i++) { if (i % bit_set_rate == 0) { bvr.bit_set(i); } }

    cout << "validate rank" << endl;
    for (int i = 0; i < validate_size; i++) {
        if (bvr.rank(i) != bvr.rank_naive(i)) { cout << "failure." << endl; return 0; }
    }
    cout << "success." << endl;

    cout << "vector size: " << bvr.vector_size() << endl;

    begin_read = system_clock::now();
    for (int i = 0; i < bvr.size; i++) { bvr.bit_read(i); }
    end_read = system_clock::now();
    cout << "access time(msec): " << duration_cast<milliseconds>(end_read - begin_read).count() << endl;

    begin_read = system_clock::now();
    for (int i = 0; i < bvr.size; i++) { bvr.rank(i); }
    end_read = system_clock::now();
    cout << "rank time(msec): " << duration_cast<milliseconds>(end_read - begin_read).count() << endl;
    cout << endl;


    cout << "# compressed  bit vector + rank #" << endl;

    compressed_bit_vector_rank cbvr(bv);

    cout << "validate rank" << endl;
    for (int i = 0; i < validate_size; i++) {
        if (cbvr.rank(i) != bvr.rank_naive(i)) { cout << "failure." << endl; return 0; }
    }
    cout << "success." << endl;

    cout << "vector size: " << cbvr.vector_size() << endl;

    begin_read = system_clock::now();
    for (int i = 0; i < cbvr.size; i++) { cbvr.access(i); }
    end_read = system_clock::now();
    cout << "access time(msec): " << duration_cast<milliseconds>(end_read - begin_read).count() << endl;

    begin_read = system_clock::now();
    for (int i = 0; i < cbvr.size; i++) { cbvr.rank(i); }
    end_read = system_clock::now();
    cout << "rank time(msec): " << duration_cast<milliseconds>(end_read - begin_read).count() << endl;
    cout << endl;

    return 0;
}
