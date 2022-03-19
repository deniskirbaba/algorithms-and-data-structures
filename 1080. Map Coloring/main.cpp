#include <iostream>
#include <vector>

using namespace std;

// struct than contains color and neighbors of country
struct Country {
    // 0 - none, 1 - red, -1 - blue
    int color = 0;

    // array that contains country neighbors
    vector<int> neighbors;
};

int main() {

    // stop flag
    bool failFlag = false;

    // reading number of countries
    int n;
    cin >> n;

    // creating array, containing countries
    vector<Country> countries(n);

    // first country is red by task condition
    countries[0].color = 1;

    // buffer
    int countryNeighbor;

    // reading and coloring 1-st country and countries that have borders with it (and with these countries)
    for (int i = 0; i < n; i++) {

        cin >> countryNeighbor;
        countryNeighbor -= 1;

        while (countryNeighbor != -1) {

            // adding neighbor in array
            countries[i].neighbors.push_back(countryNeighbor);
            countries[countryNeighbor].neighbors.push_back(i);

            // if current country (index = i) already colored
            if (countries[i].color != 0) {

                // if current neighbor (index = countryNeighbor) is not colored
                if (countries[countryNeighbor].color == 0) countries[countryNeighbor].color = -countries[i].color;

                    // if coloring is not possible
                else if (countries[countryNeighbor].color == countries[i].color) failFlag = true;
            }

            // reading next index
            cin >> countryNeighbor;
            countryNeighbor -= 1;
        }

        // if current country (index = i) don't colored yet
        if (countries[i].color == 0) {

            // check neighbors colors
            int curColor;
            int prevColor = 123;
            for (int neighbor : countries[i].neighbors) {
                curColor = countries[neighbor].color;
                if (curColor != 0) {
                    if ((curColor == prevColor) || (prevColor == 123)) {
                        prevColor = curColor;
                    }
                    else failFlag = true;
                }
            }

            if (prevColor != 123) countries[i].color = -prevColor;
        }
    }

    if (failFlag) {
        cout << -1;
        return 0;
    }

    // coloring the rest of countries
    for (int i = 0; i < n; i++) {

        // if current country (index = i) don't colored yet
        if (countries[i].color == 0) {

            // check neighbors colors
            int curColor;
            int prevColor = 123;
            for (int neighbor: countries[i].neighbors) {
                curColor = countries[neighbor].color;
                if (curColor != 0) {
                    if ((curColor == prevColor) || (prevColor == 123)) {
                        prevColor = curColor;
                    } else {
                        cout << -1;
                        return 0;
                    }
                }
            }

            if (prevColor != 123) countries[i].color = -prevColor;
        }

        // if you still not colored
        if (countries[i].color == 0) countries[i].color = -1;

    }

    // result output
    for (int i = 0; i < n; i++) {
        if (countries[i].color == 1) cout << 0;
        else if (countries[i].color == -1) cout << 1;
        else cout << -1;
    }

    /*
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int neighbor : countries[i].neighbors) {
            cout << neighbor << ' ';
        }
        cout << '\n';
    }
    */

    return 0;
}
