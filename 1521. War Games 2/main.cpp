#include <vector>
#include <iostream>

using std::cin, std::cout, std::vector;

int main() {

    uint32_t n, k;
    cin >> n >> k;

    vector<uint32_t> soldiers(n);

    for (uint32_t i = 0; i < n; i++) soldiers[i] = i + 1;

    uint32_t outIndex = k - 1;
    for (uint32_t i = 0; i < n; i++) {
        cout << soldiers[outIndex] << ' ';
        soldiers.erase(soldiers.begin() + outIndex);
        if (!soldiers.empty()) outIndex = ((outIndex + (k - 1)) % soldiers.size());
    }

    return 0;
}