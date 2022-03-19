#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// struct that represents cable
struct Cable {
    // connectors
    int a, b;

    // length
    int length;
};

// comparator (length)
bool compare(Cable first, Cable second) {
    return first.length < second.length;
}

int main() {

    // reading the number of hubs and possible connections
    int n, m;
    cin >> n >> m;

    // array of possible connections
    vector<Cable> possibleConnections;

    // the numbers of two hubs, which can be connected and the cable length required to connect them
    int a, b, l;

    // buffer
    Cable buffer;

    // reading possible connections
    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> l;
        buffer = {a - 1, b - 1, l};
        possibleConnections.push_back(buffer);
    }

    // sorting cables by descending
    sort(possibleConnections.begin(), possibleConnections.end(), compare);

    // auxiliary array for already used hubs
    vector<int> usedHubs (n, -1);
    // auxiliary array for already used cables
    vector<int> usedCables(m, 0);

    int hubValue = 0, maxLength = 0, requiredCables = 0;

    // loop through the list of all possible connections
    for (int i = 0; i < m; i++) {

        // hubs
        int &hubA = usedHubs[possibleConnections[i].a];
        int &hubB = usedHubs[possibleConnections[i].b];

        // if the hubs are already connected, then we can go further, since it will no longer be shorter due to sorting
        if (hubA != -1 and hubB != -1) continue;

        // if both hubs are not connected - connect
        else if (hubA == -1 and hubB == -1) {
            ++hubValue;
            hubA = hubValue;
            hubB = hubA;
        }

        // if only one hub connected, then connect to an existing network of a connected hub
        else if ((hubA != -1 and hubB == -1) or (hubA == -1 and hubB != -1)) {
            hubA = hubA + hubB + 1;
            hubB = hubA;
        }

        // the case of graph closure - choose the smallest level from two possible
        else {
            int minHubValue, maxHubValue;

            if (hubB > hubA) {
                minHubValue = hubA;
                maxHubValue = hubB;
            }
            else {
                minHubValue = hubB;
                maxHubValue = hubA;
            }

            for (int j = 0; j < n; j++) if (usedHubs[j] == maxHubValue) usedHubs[j] = minHubValue;
        }

        usedCables[i] = 1;
        maxLength = possibleConnections[i].length;
        ++requiredCables;
    }

    // result output
    cout << maxLength << endl << requiredCables << endl; // number of required cables and max length
    for (int j = 0; j < m; j++) if (usedCables[j])
            cout << possibleConnections[j].a + 1 << " " << possibleConnections[j].b + 1 << endl; // connections

    return 0;
}