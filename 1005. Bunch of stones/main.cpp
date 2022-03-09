#include <iostream>
#include <vector>
#include <cmath>

int main() {

    /* input of initial data */

    int n;
    std::cin >> n;

    std::vector<int> w(n); // need dynamic array (don't know length during program execution)
    for (int i = 0; i < n; i++) {
        std::cin >> w[i];
    }

    int result = n * 100000; // upper limit on the difference in the weights of two heaps

    /* realization */

    for (int combination = 0; combination < std::pow(2, n) - 1; combination++) { // enumeration of all possible combinations in two heaps

        int first_heap = 0;
        int second_heap = 0;

        for (int i = 0; i < n; i++) { // make heaps of stones by combination
            if (((combination >> i) & 1) == 0) first_heap += w[i];
            else second_heap += w[i];
        }

        int cur_difference = abs(first_heap - second_heap);

        if (cur_difference == 0) {
            result = 0;
            break;
        }
        if (cur_difference < result) result = cur_difference;
    }

    /* output of the answer */

    std::cout << result;

    return 0;
}
