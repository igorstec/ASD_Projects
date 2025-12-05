#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

// Online implpementation
class Tree {
    int idxval;
    vector<int> tree;
    int size;

public:
    Tree(int n) : idxval(2 * (1 << (31 - __builtin_clz(n)))), tree(2 * idxval, 0), size(2 * idxval) {
    }

    void update(int idx, int val) {
        if (idx < 0 || idx > size)
            throw invalid_argument("Index out of bounds for update");
        idx += idxval;
        tree[idx] += val;
        while (idx > 1) {
            idx /= 2;
            tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
        }
    }

    int rangeQuery(int l, int r) {
        if(l> idxval - 1)
            return 0;
        if (r > idxval - 1)
            r = idxval - 1;

        if (l > r || l < 0 || r > size)
            throw invalid_argument("Invalid range for query");
        l += idxval;
        r += idxval;
        int sum = 0;
        while (l <= r) {
            if (l % 2 == 1) {
                sum += tree[l];
                l++;
            }
            if (r % 2 == 0) {
                sum += tree[r];
                r--;
            }
            l /= 2;
            r /= 2;
        }
        return sum;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int> > trees;
    int maxy = 0;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        if (b > maxy)
            maxy = b;
        trees.push_back({a, b});
    }
    vector<int> results(m, 0);
    sort(trees.begin(), trees.end());
    pair<int, tuple<int, int, int> > requests[2 * m];
    Tree tree(maxy);
    for (int i = 0; i < 2 * m; i += 2) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        requests[i] = {a - 1, {c, d, i}};
        requests[i + 1] = {b, {c, d, i + 1}};
    }
    sort(requests, requests + 2 * m);
    //cout requests
    // for(int i=0; i<2*m; i++){
    //   cout<<requests[i].first<<" "<<get<0>(requests[i].second)<<" "<<get<1>(requests[i].second)<<"\n";
    // }
    int tree_idx = 0;
    for (auto request: requests) {

        while (tree_idx < n && trees[tree_idx].first <= request.first) {
            tree.update(trees[tree_idx].second, 1);
            tree_idx++;
        }

        int l = get<0>(request.second);
        int r = get<1>(request.second);
        int idx = get<2>(request.second);

        if (idx % 2 == 0) {
            // lewa granica
            results[idx / 2] -= tree.rangeQuery(l, r);
        } else {
            results[idx / 2] += tree.rangeQuery(l, r);
        }
    }


    for (int result: results) {
        cout << result << "\n";
    }
    return 0;
}
