#include <iostream>
#include <vector>

using namespace std;

// function to search for the index of the sign with the largest number excluding some index
int findMaxIndexExcept(vector<int> &roadSigns, int len, int exclusiveIndex) {

    int maxSign = 0;
    int result = -1;

    for (int i = 0; i < len; i++) {
        if (i != exclusiveIndex && roadSigns[i] > maxSign) {
            maxSign = roadSigns[i];
            result = i;
        }
    }

    return result;
}

int main() {

    // data input

    // number of different types of road signs
    int typesOfSigns;
    cin >> typesOfSigns;

    // dynamic array, containing signs
    vector<int> roadSigns(typesOfSigns);

    // total number of road signs
    int total = 0;

    // reading sings restrictions number in array
    for (int i = 0; i < typesOfSigns; i++) {
        cin >> roadSigns[i];
        total += roadSigns[i];
    }

    // previous used road sign index
    int prevSignIndex = -1;
    // the index of the max sign number
    int maxSignIndex;

    // main loop
    while (total) { // until all signs are used

        // find max sign index, exclude the previous one
        maxSignIndex = findMaxIndexExcept(roadSigns, typesOfSigns, prevSignIndex);

        // if not other signs, then use the previous
        if (maxSignIndex == -1) maxSignIndex = prevSignIndex;

        roadSigns[maxSignIndex] -= 1;
        prevSignIndex = maxSignIndex;

        // result output
        cout << maxSignIndex + 1 << ' ';

        total--;
    }

    return 0;
}