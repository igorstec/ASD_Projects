#include <iostream>
#include <list>
#include <vector>
#include <queue>

using namespace std;

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<int, list<int> > > dependencies(n + 1, {0, list<int>()});
    vector<int> project_cost(n + 1);
    priority_queue<pair<int, int> > pq;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        project_cost[i] = a;
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        dependencies[a].first++;
        dependencies[b].second.push_back(a);
    }
    int to_return = 0;
    int visits_left = k;
    for (int i = 1; i <= n; i++) {
        if (dependencies[i].first == 0) {
            pq.emplace(-project_cost[i], i);
        }
    }
    while (visits_left > 0 && !pq.empty()) {
        pair<int, int> current = pq.top();
        pq.pop();
        //cout<<"Taking project "<<current.second<<" with cost "<<-current.first<<endl;
        to_return = max(to_return, -current.first);
        visits_left--;
        for (int neighbor: dependencies[current.second].second) {
            dependencies[neighbor].first--;
            if (dependencies[neighbor].first == 0) {
                pq.emplace(-project_cost[neighbor], neighbor);
            }
        }
    }
    cout << to_return << endl;
    return 0;
}
