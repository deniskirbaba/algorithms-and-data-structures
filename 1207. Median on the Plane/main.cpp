#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define M_PI 3.14159265358979323846

// a structure for storing the coordinates of a point, its ordinal number,
// the angle of a straight line passing through this point, as well as the method for calculating the angle
struct Dot {
    // coordinates
    int x;
    int y;

    // ordinal number
    int id;

    // angle of a straight line
    double angle;

    // method for calculating the angle
    void calculateAngle(Dot minDot) {

        // if on one vertical line
        if (minDot.x == this->x) this->angle = M_PI/2;

        // if on one horizontal line
        else if (minDot.y == this->y) this->angle = 0;

        // calculation in other cases
        else this->angle = atan((double)(this->y - minDot.y)/(double)(this->x - minDot.x));

        // convert the angle to a range of positive numbers
        if (this->angle < 0) this->angle += 2 * M_PI;
    }
};

// just swapping dots function
void swap(Dot* first, Dot* second) {
    Dot buffer = *first;
    *first = *second;
    *second = buffer;
}

// my implementation of quick sort
void quickSort(vector<Dot> &dots, int left, int right) {

    int i = left, j = right;

    // pivot element
    double pivot = dots[(left + right) / 2].angle;

    // main loop
    while(i <= j) {
        while (dots[i].angle < pivot) i++;
        while (dots[j].angle > pivot) j--;
        if (i > j) break;
        swap(&dots[i], &dots[j]);
        i++;
        j--;
    }
    if (left < j) quickSort(dots, left, j);
    if (i < right) quickSort(dots, i, right);
}

int main() {

    // reading the number of points
    int n;
    cin >> n;

    // array containing points
    vector<Dot> dots(n);

    // minimum y dot
    Dot minDot = {1000001, 1000001, 0};

    // reading dots into array
    for (int i = 0; i < n; i++) {
        // saving coordinates
        cin >> dots[i].x >> dots[i].y;
        // saving id
        dots[i].id = i + 1;

        // choose the minimum y point
        if (dots[i].y < minDot.y or dots[i].y == minDot.y and dots[i].x < dots[minDot.id].x) {
            minDot.y = dots[i].y;
            minDot.id = i;
        }
    }

    // push min dot at the start of array
    swap(&dots[0], &dots[minDot.id]);

    // calculate angles relative to the min (first) dot
    for (int i = 1; i < n; i++) dots[i].calculateAngle(dots[0]);

    // sorting by ascending angle
    quickSort(dots, 1, n - 1);

    // result output - min dot and mean by angle dot
    cout << dots[0].id << " " << dots[n / 2].id << endl;

    return 0;
}