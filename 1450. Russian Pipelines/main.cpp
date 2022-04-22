#include <iostream>
#include <vector>

using std::cin, std::cout, std::vector;

struct pipeLine {
    uint16_t a, b;
    uint32_t c;

    pipeLine(int a = 0) {
        cin >> this->a >> this->b >> this->c;
    }
};

int64_t dijkstra(vector<pipeLine> &net, uint16_t s, uint16_t n, uint32_t m, uint16_t f)
{ // Dijkstra algorithm for max weight path in one-directional graph
    vector<int64_t> path(n + 1, -1);
    path[s] = 0;
    for (uint16_t i = 1; i < n; i++) for (uint32_t j = 0; j < m; j++)
            if (path[net[j].a] != -1 and path[net[j].b] < path[net[j].a] + net[j].c)
                path[net[j].b] = path[net[j].a] + net[j].c;
    return path[f];
}

int main() {
    uint16_t n;
    uint32_t m;
    cin >> n >> m;

    vector<pipeLine> net;
    for (uint32_t i = 0; i < m; i++) net.push_back(pipeLine());

    uint16_t s, f;
    cin >> s >> f;

    int64_t res = dijkstra(net, s, n, m, f);
    (res != -1) ? cout << res : cout << "No solution";

    return 0;
}