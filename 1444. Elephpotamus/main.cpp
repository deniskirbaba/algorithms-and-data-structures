#include <iostream>
#include <cmath>

using std::cin, std::qsort, std::cout;

#define PI 3.14159265;

struct pumpkin {
    uint32_t d; // distance from the origin
    double ang; // angle from the origin
    uint16_t id;

    void create(int16_t x0, int16_t y0, uint16_t index) {
        int16_t x, y;
        cin >> x >> y;
        this->id = index + 1;
        this->d = (x - x0) * (x - x0) + (y - y0) * (y - y0);
        this->ang = atan2(y - y0, x - x0) * 180.0 / PI;
        if (y - y0 < 0) this->ang += 360; // make all angles positive
    }
};

int compare(const void *a, const void *b) {
    const pumpkin *p1 = (pumpkin*) a;
    const pumpkin *p2 = (pumpkin*) b;
    if (p1->ang - p2->ang > 1e-10) return 1; // angle is 1 priority
    else if (p1->ang - p2->ang < -1e-10) return -1;
    else if (p1->d > p2->d) return 1; // distance is 2 priority
    else return -1;
}

int main() {
    uint16_t n;
    int16_t x0, y0; // origin
    cin >> n >> x0 >> y0;
    pumpkin field[n];
    field[0] = (pumpkin){0, -1,1}; // for avoiding error while sort
    for (uint16_t i = 1; i < n; i++) field[i].create(x0, y0, i);

    qsort(field, n, sizeof(pumpkin), compare);

    uint16_t start = 1;
    for (uint16_t i = 1; i < n - 1; i++) // if an angle > 180 - path crossing
        if (field[i + 1].ang - field[i].ang > 179.999) start = i + 1;

    cout << n << '\n' << 1 << '\n';

    for (uint16_t i = start; i < n; i++) cout << field[i].id << '\n';
    for (uint16_t i = 1; i < start; i++) cout << field[i].id << '\n';

    return 0;
}