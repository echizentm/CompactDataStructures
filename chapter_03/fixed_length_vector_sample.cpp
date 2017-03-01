#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>
#include "fixed_length_vector.h"


using namespace std;
using namespace std::chrono;
using namespace cds;


bool run_vector(int length, int num) {
    vector<unsigned int> vec(num);
    vector<int> range(num);
    iota(range.begin(), range.end(), 0);
    int mod = pow(2, length);

    cout << "run vector (length = " << length << ")" << endl;
    auto begin_write = system_clock::now();
    for (auto i : range) { vec[i] = i % mod; }
    auto end_write = system_clock::now();
    cout << "msec to write: " << duration_cast<milliseconds>(end_write - begin_write).count() << endl;

    int count = 0;
    auto begin_read = system_clock::now();
    for (auto i : range) { if (vec[i] == (i % mod)) { count++; }; }
    auto end_read = system_clock::now();
    cout << "size of vector: " << vec.size() << endl;
    cout << "rate of success: " << count << " / " << range.size() << endl;
    cout << "msec to read: " << duration_cast<milliseconds>(end_read - begin_read).count() << endl;
    cout << endl;
    return count == range.size();
}


bool run_fixed_length_vector(int length, int num, bool is_rapid) {
    fixed_length_vector vec(length, num, is_rapid);
    vector<int> range(num);
    iota(range.begin(), range.end(), 0);
    int mod = pow(2, length);

    cout << "run fixed length vec (length = " << length << ", is_rapid = " << is_rapid << ")" << endl;
    auto begin_write = system_clock::now();
    for (auto i : range) { vec.write(i, i % mod); }
    auto end_write = system_clock::now();
    cout << "msec to write: " << duration_cast<milliseconds>(end_write - begin_write).count() << endl;

    int count = 0;
    auto begin_read = system_clock::now();
    for (auto i : range) { if (vec.read(i) == (i % mod)) { count++; }; }
    auto end_read = system_clock::now();
    cout << "size of vector: " << vec.vector_size() << endl;
    cout << "rate of success: " << count << " / " << range.size() << endl;
    cout << "msec to read: " << duration_cast<milliseconds>(end_read - begin_read).count() << endl;
    cout << endl;
    return count == range.size();
}


int main(int argc, char **argv) {
    int num = 1000 * 1000;

    vector<int> range(sizeof(int) * 4 - 1);
    iota(range.begin(), range.end(), 1);
    for (auto length : range) {
        if (!run_vector(length, num)) { cout << "failure!" << endl; return 1; }
        if (!run_fixed_length_vector(length, num, true)) { cout << "failure!" << endl; return 1; }
        if (!run_fixed_length_vector(length, num, false)) { cout << "failure!" << endl; return 1; }
    }
    return 0;
}
