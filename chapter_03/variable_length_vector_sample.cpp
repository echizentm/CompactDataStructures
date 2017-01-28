#include <iostream>
#include <vector>
#include "sampled_pointers.h"
#include "dense_pointers.h"


using namespace std;
using namespace cds;


int main(int argc, char **argv) {
    sampled_pointers sp;
    dense_pointers dp(3);
    vector<int> numbers = {0, 1, 0, 2, 5, 1, 3, 2, 8, 2};

    for (auto number : numbers) {
        sp.push_back(number);
        dp.push_back(number);
        cout << number << " ";
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

    return 0;
}
