#include <iostream>
#include <set>
#include <vector>

using std::cin, std::cout, std::vector, std::set;

int res = 0;

set<uint16_t> count(const set<uint16_t>& collection, uint16_t maxSize) {
    uint16_t prev = 0;
    set<uint16_t> singleElements;
    for(uint16_t cur : collection){
        if (cur - prev > 2) res++; // if at least two whites in a row: res++
        else if (cur - prev == 2) singleElements.insert(cur - 1); // Otherwise, add to the cells-singles array
        prev = cur;
    }
    if (maxSize - prev > 1) res++; // if the last one is bad worth not extreme: res++
    else if (maxSize - prev == 1) singleElements.insert(maxSize); // If penultimate, then add to the cells-singles array
    return singleElements; // Now the output is an array of singles in a specific line / row
}

int main() {
    uint16_t m, n, k, x, y;
    cin >> m >> n >> k;

    // dynamic arrays with sorting
    vector<set<uint16_t>> blackX(m);
    vector<set<uint16_t>> blackY(n);

    while(k--){
        cin >> x >> y;
        blackX[x - 1].insert(y); // array х -> у
        blackY[y - 1].insert(x); // array y -> x
    }

    for(set<uint16_t>& setX : blackX) setX = count(setX, n); // counting stripes on x
    for(set<uint16_t>& setY : blackY) setY = count(setY, m); // counting stripes on y
    for (uint16_t i = 0; i < m; i++) for (uint16_t j : blackX[i]) // counting the cells-singles
            if (blackY[j - 1].find(i + 1) != blackY[j - 1].end()) res++;

    cout << res << '\n';

    return 0;
}