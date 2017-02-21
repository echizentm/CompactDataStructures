#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>
#include "variable_length_vector.h"


using namespace std;
using namespace std::chrono;
using namespace cds;


bool run_variable_length_vector(
    variable_length_vector& vec, int length, int num, const char *class_name
) {
    vector<int> range(num);
    iota(range.begin(), range.end(), 0);
    int mod = pow(2, length);

    cout << "run variable length vec (length = " << length << ", class_name = " << class_name << ")" << endl;
    auto begin_write = system_clock::now();
    for (auto i : range) { vec.push_back(i % mod); }
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
        sampled_pointers sp;
        dense_pointers dp(length);
        direct_access_codes dac(2);
        elias_fano_codes efc;
        if (!run_variable_length_vector(sp, length, num, "sampled pointers")) { cout << "failure!" << endl; return 1; }
        if (!run_variable_length_vector(dp, length, num, "dense pointers")) { cout << "failure!" << endl; return 1; }
        if (!run_variable_length_vector(dac, length, num, "direct access codes")) { cout << "failure!" << endl; return 1; }
        if (!run_variable_length_vector(efc, length, num, "elias fano codes")) { cout << "failure!" << endl; return 1; }
    }
    return 0;
}
