#include <iostream>
#include <vector>
#include <math.h>
#include <map>
#include <algorithm>


using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int s = 0) : val(s), left(nullptr), right(nullptr) {
    }
};

class PersistentSegmentTree {
private:
    vector<TreeNode *> roots_; // Snapshots at each time point
    int tree_size_;

    // Recursively update and create new path
    TreeNode *update(TreeNode *node, int l, int r, int idx) {
        if (!node) {
            node = new TreeNode(0);
        }

        if (l == r) {
            // Leaf node - increment count
            auto *new_node = new TreeNode(node->val + 1);
            return new_node;
        }

        auto *new_node = new TreeNode(node->val);
        int mid = l + (r - l) / 2;

        if (idx <= mid) {
            new_node->left = update(node->left, l, mid, idx);
            new_node->right = node->right;
        } else {
            new_node->left = node->left;
            new_node->right = update(node->right, mid + 1, r, idx);
        }

        // Propagate val upwards
        new_node->val = 0;
        if (new_node->left) new_node->val += new_node->left->val;
        if (new_node->right) new_node->val += new_node->right->val;

        return new_node;
    }

    // Query val in range [query_l, query_r] at time snapshot
    int query(TreeNode *node, int l, int r, int query_l, int query_r) {
        if (!node || query_l > r || query_r < l) {
            return 0;
        }

        // Current range is completely inside query range
        if (query_l <= l && r <= query_r) {
            return node->val;
        }

        int mid = l + (r - l) / 2;
        int left_val = query(node->left, l, mid, query_l, query_r);
        int right_val = query(node->right, mid + 1, r, query_l, query_r);

        return left_val + right_val;
    }

public:
    // Initialize tree with given max value
    explicit PersistentSegmentTree(int max_val) : tree_size_(max_val) {
        // Create initial empty root
        roots_.push_back(new TreeNode(0));
    }

    // Add update at current time point
    void update(int idx) {
        if (idx < 0 || idx >= tree_size_) {
            return; // Out of bounds
        }
        TreeNode *new_root = update(roots_.back(), 0, tree_size_ - 1, idx);
        roots_.push_back(new_root);
    }

    // Query range [l, r] between time points time_l and time_r (inclusive)
    // Returns: count of elements in range that were updated between these times
    int rangeQuery(int l, int r, int time_l, int time_r) {
        if (time_l < 0 || time_r >= roots_.size() || time_l > time_r) {
            return 0;
        }

        if (l > r || l < 0 || r >= tree_size_) {
            return 0;
        }

        // Query difference: state at time_r minus state at time_l
        int val_r = query(roots_[time_r], 0, tree_size_ - 1, l, r);
        int val_l = query(roots_[time_l], 0, tree_size_ - 1, l, r);

        return val_r - val_l;
    }

    // Get current time (number of snapshots - 1)
    int getCurrentTime() {
        return roots_.size() - 1;
    }
};

// ===================== Persistent Segment Index Tree =================
// Used to find minimum index in a range at a specific time point

class PersistentSegmentIndexTree {
private:
    int maxval_;
    int tree_size_;
    vector<TreeNode *> roots_; // Snapshots at each time point


    void build(TreeNode *n, int low, int high) {
        if (low == high) {
            n->val = maxval_; // infinity
            return;
        }
        int mid = (low + high) / 2;
        n->left = new TreeNode(maxval_);
        n->right = new TreeNode(maxval_);
        build(n->left, low, mid);
        build(n->right, mid + 1, high);
        n->val = min(n->left->val, n->right->val);
    }

    /**
 * Upgrades to new Version
 * @param prev : points to node of previous version
 * @param cur  : points to node of current version
 * Time Complexity : O(logn)
 * Space Complexity : O(logn)  */
    void upgrade(TreeNode *prev, TreeNode *cur, int low, int high,
                 int idx, int value) {
        if (idx > high or idx < low or low > high)
            return;

        if (low == high) {
            // modification in new version
            cur->val = value;
            return;
        }
        int mid = (low + high) / 2;
        if (idx <= mid) {
            // link to right child of previous version
            cur->right = prev->right;

            // create new node in current version
            cur->left = new TreeNode(maxval_);

            upgrade(prev->left, cur->left, low, mid, idx, value);
        } else {
            // link to left child of previous version
            cur->left = prev->left;

            // create new node for current version
            cur->right = new TreeNode(maxval_);

            upgrade(prev->right, cur->right, mid + 1, high, idx, value);
        }

        // calculating data for current version
        // by combining previous version and current
        // modification
        cur->val = min(cur->left->val, cur->right->val);
    }

    int query(TreeNode *n, int low, int high, int l, int r) {
        if (l > high or r < low or low > high)
            return maxval_; // infinity
        if (l <= low and high <= r)
            return n->val;
        int mid = (low + high) / 2;
        int p1 = query(n->left, low, mid, l, r);
        int p2 = query(n->right, mid + 1, high, l, r);
        return min(p1, p2);
    }

public:
    //size to ile elementow ma przechowywac
    PersistentSegmentIndexTree(int size, int maxval) {
        maxval_ = maxval;
        tree_size_ = size;
        TreeNode *root = new TreeNode(maxval);
        build(root, 0, size);
        roots_.push_back(root);
    }

    int query(int l, int r, int time) {
        if (time < 0 || time >= roots_.size())
            return maxval_; // infinity
        return query(roots_[time], 0, tree_size_ - 1, l, r);
    }

    void update(int idx, int value) {
        if (idx < 0 || idx >= tree_size_)
            return;
        TreeNode *new_root = new TreeNode(maxval_);
        upgrade(roots_.back(), new_root, 0, tree_size_ - 1, idx, value);
        roots_.push_back(new_root);
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;


    vector<int> original_value;


    map<int, int> compress;

    // Read stock indices and create snapshots
    for (int i = 0; i < n; i++) {
        int idx;
        cin >> idx;
        original_value.push_back(idx);
    }
    vector<int> stock_indices = original_value;

    sort(original_value.begin(), original_value.end());
    original_value.erase(unique(original_value.begin(), original_value.end()), original_value.end());
    for (int i = 0; i < original_value.size(); i++) {
        compress[original_value[i]] = i;
    }

    PersistentSegmentTree tree(original_value.size());
    for (int i = 0; i < n; i++) {
        int compressed_idx = compress[stock_indices[i]];
        tree.update(compressed_idx);
    }
    PersistentSegmentIndexTree index_tree(original_value.size(), n);
    for (int i = n - 1; i >= 0; i--) {
        int compressed_idx = compress[stock_indices[i]];
        index_tree.update(compressed_idx, i);
    }

    // Process queries
    for (int i = 0; i < m; i++) {
        int time_start, time_end, range_l, range_r;
        cin >> time_start >> time_end >> range_l >> range_r;

        auto itL = compress.lower_bound(range_l); // pierwsza wartość >= range_l
        auto itR = compress.upper_bound(range_r); // pierwsza wartość > range_r

        if (itL == compress.end() || itR == compress.begin()) {
            // brak wartości w [range_l, range_r]
            cout << -1 << " " << 0 << "\n";
            continue;
        }
        --itR; // teraz itR wskazuje na ostatnią wartość <= range_r

        int L = itL->second;
        int R = itR->second;
        if (L > R) {
            cout << -1 << " " << 0 << "\n";
            continue;
        }

        int count = tree.rangeQuery(L, R, time_start - 1, time_end);
        if (count == 0) {
            cout << -1 << " " << 0 << "\n";
        } else {
            //cout<<"Szukam w przedziale: "<<L<<" "<<R<<" i po wprowadzeniu: "<<n - time_start+1<<"\n";
            int found_index = index_tree.query(L, R, n - time_start + 1);
            cout << found_index + 1 << " " << count << "\n";
        }
    }

    return 0;
}
