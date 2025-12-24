#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, m, to_return = INT_MAX;
    cin >> n >> m;
    queue<int> verties_left;
    vector<pair<int, int> > distances(n, {INT_MAX, INT_MAX}); //cost to a from start, cost from a to end
    verties_left.push(0);
    vector<list<pair<int,int>> > graph(n);
    vector<list<pair<int,int>> > inverted_graph(n);
    vector<bool> visited(n, false);

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].emplace_back(b, c);
        inverted_graph[b].emplace_back(a, c);
    }
    distances[0].first = 0;
    while (!verties_left.empty()) {
        int current = verties_left.front();
        verties_left.pop();
        visited[current] = true;
        for(auto [neighbour, cost] : graph[current]) {
            int new_cost = distances[current].first + cost;
            if(new_cost < distances[neighbour].first) {
                distances[neighbour].first = new_cost;
            }
            if(!visited[neighbour]) {
                verties_left.push(neighbour);
            }
        }
    }
    fill(visited.begin(), visited.end(), false);
    distances[n-1].second = 0;
    verties_left.push(n-1);
    while (!verties_left.empty()) {
        int current = verties_left.front();
        verties_left.pop();
        visited[current] = true;
        for(auto [neighbour, cost] : inverted_graph[current]) {
            int new_cost = distances[current].second + cost;
            if(new_cost < distances[neighbour].second) {
                distances[neighbour].second = new_cost;
            }
            if(!visited[neighbour]) {
                verties_left.push(neighbour);
            }
        }
    }
    for(int i=0; i<n; i++) {
        if(distances[i].first != INT_MAX && distances[i].second != INT_MAX) {
            to_return = min(to_return, max(distances[i].first ,distances[i].second));
        }
    }

    cout << to_return << endl;
    return 0;
}
