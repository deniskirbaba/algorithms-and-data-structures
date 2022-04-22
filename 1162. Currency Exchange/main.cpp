#include <iostream>
#include <vector>

using std::cin, std::vector, std::cout, std::max;

struct exchangePoint
{
    uint8_t a, b;
    double r, c;
};

int main()
{
    uint8_t n, m, s;
    double v;
    cin >> n >> m >> s >> v;

    vector<exchangePoint> exchangePoints;

    vector<double> profit(n + 1, 0.000);
    profit[s] = v;

    uint8_t a, b;
    double rab, cab, rba, cba;

    for (uint8_t i = 0; i < m; i++) {
        cin >> a >> b >> rab >> cab >> rba >> cba;
        exchangePoints.push_back({a, b, rab, cab}); // direct convert
        exchangePoints.push_back({b, a, rba, cba}); // inverse convert
    }

    for (uint8_t i = 0; i < n - 1; i++) for (auto & exPoint : exchangePoints) {
            profit[exPoint.b] = max((profit[exPoint.a] - exPoint.c) * exPoint.r, profit[exPoint.b]);
        } // choosing the most profitable point of currency exchange for the i-th and the result of the exchange

    for (auto & exPoint : exchangePoints) if ((profit[exPoint.a] - exPoint.c) * exPoint.r > profit[exPoint.b]) {
            cout << "YES" << '\n'; // if we can get profit
            return 0;
        }

    cout << "NO" << '\n';

    return 0;
}