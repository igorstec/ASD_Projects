#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, m;
    long long to_return = LLONG_MAX;
    cin >> n >> m;
    priority_queue<pair<long long,int>> verties_left; // cost to get to a vertix, vertix
    vector<pair<long long, long long> > distances(n, {LLONG_MAX, LLONG_MAX}); //cost to a from start, cost from a to end
    verties_left.emplace(0, 0);
    vector graph(n, vector<pair<int, int> >());
    vector inverted_graph(n, vector<pair<int, int> >());

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].emplace_back(b, c);
        inverted_graph[b].emplace_back(a, c);
    }
    distances[0].first = 0;
    while (!verties_left.empty()) {
        int current = verties_left.top().second;
        long long current_cost = -verties_left.top().first;
        verties_left.pop();
        for (auto [neighbour, cost]: graph[current]) {
            long long new_cost = current_cost + cost;
            if (new_cost < distances[neighbour].first) {
                distances[neighbour].first = new_cost;
                verties_left.emplace(-distances[neighbour].first, neighbour);
            }

        }
    }
    distances[n - 1].second = 0;
    verties_left.emplace(0, n - 1);
    while (!verties_left.empty()) {
        int current = verties_left.top().second;
        long long current_cost = -verties_left.top().first;
        verties_left.pop();
        for (auto [neighbour, cost]: inverted_graph[current]) {
            long long new_cost = current_cost + cost;
            if (new_cost < distances[neighbour].second) {
                distances[neighbour].second = new_cost;
                verties_left.emplace(-distances[neighbour].second, neighbour);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        to_return = min(to_return, max(distances[i].first, distances[i].second));
    }

    cout << to_return << endl;
    return 0;
}
