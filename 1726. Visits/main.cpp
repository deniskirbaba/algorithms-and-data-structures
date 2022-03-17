#include <iostream>
#include <vector>

using namespace std;

// just swapping dots function
void swap(int* first, int* second) {
    int buffer = *first;
    *first = *second;
    *second = buffer;
}

// my implementation of quick sort
void quickSort(vector<int> &vec, long long left, long long right) {
    long long i = left;
    long long j = right;
    long long mid = left + (right - left) / 2;

    // pivot element
    int piv = vec[mid];

    // main loop
    while (i<right || j>left) {
        while (vec[i] < piv) i++;
        while (vec[j] > piv) j--;
        if (i <= j) {
            swap(&vec[i],&vec[j]);
            i++; j--;
        } else {
            if (i < right) quickSort(vec, i, right);
            if (j > left) quickSort(vec, left, j);
            return;
        }
    }
}

int main() {

    // data input
    long long n;
    cin >> n;

    vector<int> xCoords(n);
    vector<int> yCoords(n);

    for (long long i = 0; i < n; i++) cin >> xCoords[i] >> yCoords[i];

    // sorting arrays
    quickSort(xCoords, 0, n - 1);
    quickSort(yCoords, 0, n - 1);

    // sum coords
    long long sum = 0;
    for (long long i = 1; i < n; i++) {

        // calculation of the distance in coordinates to the neighboring house
        int xNearestHouse = xCoords[i] - xCoords[i - 1];
        int yNearestHouse = yCoords[i] - yCoords[i - 1];

        // the sum of the distances traveled along the road section in the direction of large (n-i)
        // and in the direction of smaller (i) coordinates
        // counts twice as there must be a way back to your home
        sum += (xNearestHouse + yNearestHouse) * i * (n - i) * 2;
    }

    // calculate mean value of path
    sum = sum / (n * (n - 1));

    // result input
    cout << sum << endl;

    return 0;
}
