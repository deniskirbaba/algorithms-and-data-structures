#include <vector>
#include <queue>
#include <iostream>

using namespace std;

// struct than contains color and neighbors of country
struct Country {
    // -1 - none, 0 - red, 1 - blue
    int color = -1;

    // array that contains country neighbors
    vector<int> neighbors;
};

int main() {

    // reading number of countries
    int n;
    cin >> n;

    // creating array, containing countries
    // So that the numbering of countries goes from 1 and not from 0
    vector<Country> countries(n + 1);

    // buffer
    int countryNeighbor;

    // reading countries
    for (int i = 1; i <= n; i++) {

        cin >> countryNeighbor;

        while (countryNeighbor != 0) {

            // adding neighbor in array
            countries[i].neighbors.push_back(countryNeighbor);
            countries[countryNeighbor].neighbors.push_back(i);
            cin >> countryNeighbor;
        }
    }

    // coloring countries
    for (int i = 1; i <= n; i++) {

        // if current country don't colored yet
        if (countries[i].color == -1) {
            queue<int> countriesQueue;
            countriesQueue.push(i);
            countries[i].color = 0;

            // while we have at least one element in the queue
            while (!countriesQueue.empty()) {

                // retrieve the first element of the queue
                int first = countriesQueue.front(); countriesQueue.pop();

                // check if the country has a border with a country with the same color
                for (int i = 0; i < countries[first].neighbors.size(); i++) {
                    int neighbour = countries[first].neighbors[i];

                    // if neighboring countries are the same color
                    if (countries[first].color == countries[neighbour].color) {
                        cout << "-1";
                        exit(0);
                    }

                    // if not, then we paint it in a color different from the color of the current country
                    // and add a country to the queue to check
                    if (countries[neighbour].color == -1) {
                        countries[neighbour].color = (countries[first].color == 0 ? 1 : 0);
                        countriesQueue.push(neighbour);
                    }
                }
            }
        }
    }

    // result output
    for (int i = 1; i <= n; i++) cout << countries[i].color;

    return 0;
}