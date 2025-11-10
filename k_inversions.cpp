#include <iostream>
#include <vector>
#include <thread>

using namespace std;

#define MOD 1000000000

class FenwickTree {
    vector<long long> tree;
    int n;

public:
    FenwickTree(int size) : n(size), tree(size + 1, 0) {}

    void update(int idx, long long val) {
        for (int i = idx; i <= n; i += i & -i) {
            tree[i] = (tree[i] + val) % MOD;
        }
    }

    long long query(int idx) {
        long long sum = 0;
        for (int i = idx; i > 0; i -= i & -i) {
            sum = (sum + tree[i]) % MOD;
        }
        return sum;
    }

    long long rangeQuery(int l, int r) {
        if (l > r) return 0;
        return (query(r) - query(l - 1) + MOD) % MOD;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // k drzew Fenwicka - jedno dla każdej długości
    vector bit(k + 1, FenwickTree(n));

    long long result = 0;

    for (int i = 1; i <= n; i++) {
        bit[1].update(a[i], 1);
        for (int len = k; len >= 2; len--) {
            long long cnt = bit[len - 1].rangeQuery(a[i] + 1, n);
            bit[len].update(a[i], cnt);

            if (len == k) {
                result = (result + cnt) % MOD;
            }
        }
    }
    cout << result << "\n";

    return 0;
}
