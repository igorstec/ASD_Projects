#include <iostream>
#include <vector>
#include <math.h>
#include <map>
#include <algorithm>


using namespace std;

struct TreeNode {
    int sum;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int s = 0) : sum(s), left(nullptr), right(nullptr) {}
};

class PersistentSegmentTree {
private:
    vector<TreeNode*> roots_;  // Snapshots at each time point
    int tree_size_;

    // Recursively update and create new path
    TreeNode* update(TreeNode* node, int l, int r, int idx) {
        if (!node) {
            node = new TreeNode(0);
        }

        if (l == r) {
            // Leaf node - increment count
            auto* new_node = new TreeNode(node->sum + 1);
            return new_node;
        }

        auto* new_node = new TreeNode(node->sum);
        int mid = l + (r - l) / 2;

        if (idx <= mid) {
            new_node->left = update(node->left, l, mid, idx);
            new_node->right = node->right;
        } else {
            new_node->left = node->left;
            new_node->right = update(node->right, mid + 1, r, idx);
        }

        // Propagate sum upwards
        new_node->sum = 0;
        if (new_node->left) new_node->sum += new_node->left->sum;
        if (new_node->right) new_node->sum += new_node->right->sum;

        return new_node;
    }

    // Query sum in range [query_l, query_r] at time snapshot
    int query(TreeNode* node, int l, int r, int query_l, int query_r) {
        if (!node || query_l > r || query_r < l) {
            return 0;
        }

        // Current range is completely inside query range
        if (query_l <= l && r <= query_r) {
            return node->sum;
        }

        int mid = l + (r - l) / 2;
        int left_sum = query(node->left, l, mid, query_l, query_r);
        int right_sum = query(node->right, mid + 1, r, query_l, query_r);

        return left_sum + right_sum;
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
            return;  // Out of bounds
        }
        TreeNode* new_root = update(roots_.back(), 0, tree_size_ - 1, idx);
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
        int sum_r = query(roots_[time_r], 0, tree_size_ - 1, l, r);
        int sum_l = query(roots_[time_l], 0, tree_size_ - 1, l, r);

        return sum_r - sum_l;
    }

    // Get current time (number of snapshots - 1)
    int getCurrentTime() {
        return roots_.size() - 1;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;


    vector<int>original_value;


    map<int, int> compress;

    // Read stock indices and create snapshots
    for (int i = 0; i < n; i++) {
        int idx;
        cin >> idx;
        original_value.push_back(idx);
    }
    vector<int> stock_indices=original_value;

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

    // Process queries
    for (int i = 0; i < m; i++) {
        int time_start, time_end, range_l, range_r;
        cin >> time_start >> time_end >> range_l >> range_r;

        auto itL = compress.lower_bound(range_l);     // pierwsza wartość >= range_l
        auto itR = compress.upper_bound(range_r);     // pierwsza wartość > range_r

        if (itL == compress.end() || itR == compress.begin()) {
            // brak wartości w [range_l, range_r]
            cout << -1 << " " << 0 << "\n";
            continue;
        }
        --itR;  // teraz itR wskazuje na ostatnią wartość <= range_r

        int L = itL->second;
        int R = itR->second;
        if (L > R) {
            cout << -1 << " " << 0 << "\n";
            continue;
        }

        int count = tree.rangeQuery(L, R, time_start - 1, time_end);
        if(count == 0) {
            cout << -1 << " "<<0<<"\n";
        }else {
            for(int idx = time_start-1; idx <= time_end; idx++) {
                if( stock_indices[idx] >= range_l && stock_indices[idx] <= range_r) {
                    cout << idx+1 << " " << count << "\n";
                    break;
                }
            }
        }
    }

    return 0;
}