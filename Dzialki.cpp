#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <map>

using namespace std;

// Online implpementation
class Tree {
    int idxval;
    vector<int> tree;
    int size;
    map<int, int> compress_;
    int maxval_;

public:
    Tree(int n, map<int, int> compress, int maxval) : idxval(2 * (1 << (31 - __builtin_clz(n)))), tree(2 * idxval, 0), compress_(std::move(compress)), size(2 * idxval), maxval_(compress_[maxval]) {
    }

    void update(int idx, int val) {
        //udate tylko na realnych idx czyli
        idx = compress_[idx];
        if (idx < 0 || idx > idxval -1)
            return;
        idx += idxval;
        tree[idx] += val;
        while (idx > 1) {
            idx /= 2;
            tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
        }
    }

    int rangeQuery(int l, int r) {
        l = compress_[l];
        r = compress_[r];
        if(l > maxval_)
            return 0;
        if (r > maxval_)
            r = maxval_;

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
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, maxval = 0;
    cin >> n >> m;

    vector<pair<int, int> > trees(n);
    vector<int> all_y;

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        if(b>maxval)
            maxval = b;
        all_y.push_back(b);
        trees[i] = {a, b};
    }

    sort(trees.begin(), trees.end());

    vector<tuple<int, int, int, int>> requests;

    for (int i = 0; i < 2 * m; i += 2) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        requests.push_back( {a - 1, c, d, i});
        requests.push_back({b, c, d, i + 1});
        all_y.push_back(c);
        all_y.push_back(d);
    }
    sort(all_y.begin(), all_y.end());
    all_y.erase(unique(all_y.begin(), all_y.end()), all_y.end());

    sort(requests.begin(), requests.end());

    map<int, int> compress;

    for (int i = 0; i < all_y.size(); i++) {
        compress[all_y[i]] = i;
    }

    Tree tree((int)all_y.size(), std::move(compress), maxval);

    vector<int> results(m, 0);
    int tree_idx = 0;
    for (auto request: requests) {

        while (tree_idx < n && trees[tree_idx].first <= get<0>(request)) {
            tree.update(trees[tree_idx].second, 1);
            tree_idx++;
        }

        int l = get<1>(request);
        int r = get<2>(request);
        int idx = get<3>(request);

        if (idx % 2 == 0) {
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
