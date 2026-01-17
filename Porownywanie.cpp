#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

// Rabin Karp Algorithm
// function RabinKarp(string s[1..n], string pattern[1..m])
//     hpattern := hash(pattern[1..m]);
// for i from 1 to n-m+1
//     hs := hash(s[i..i+m-1])
//     if hs = hpattern
//         if s[i..i+m-1] = pattern[1..m]
//             return i
// return not found

using ll = long long;
vector<ll> h;
vector<ll> p;

const ll MOD = 1e9 + 7;
const ll P = 313;

// H(L, R) = (h[R] - h[L-1] * P^(R-L+1)) % MOD
ll getHash(int L, int R) {
    if (L > R) return 0;
    ll res = (h[R] - (h[L - 1] * p[R - L + 1]) % MOD) % MOD;
    if (res < 0) res += MOD;
    return res;
}

int getLCP(int start1, int start2, int max_len) {
    int left = 0, right = max_len;
    int res = 0;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (mid == 0) {
            left = 1;
            continue;
        }

        if (getHash(start1, start1 + mid - 1) == getHash(start2, start2 + mid - 1)) {
            res = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return res;
}

bool solve_query(int a, int b, int c, int d) {
    int len1 = b - a + 1;
    int len2 = d - c + 1;

    if (std::abs(len1 - len2) >= 2) return false;

    if (len1 == len2 && getHash(a, b) == getHash(c, d)) return true;

    int common = getLCP(a, c, min(len1, len2));

    if (len1 == len2) {
        int remaining = len1 - common - 1;
        if (remaining == 0) return true;

        if (getHash(a + common + 1, b) == getHash(c + common + 1, d)) {
            return true;
        }
    } else {
        int long_start = (len1 > len2) ? a : c;
        int long_end = (len1 > len2) ? b : d;
        int short_start = (len1 > len2) ? c : a;
        int short_end = (len1 > len2) ? d : b;

        if (common == min(len1, len2)) return true;

        if (getHash(long_start + common + 1, long_end) == getHash(short_start + common, short_end)) {
            return true;
        }
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    string s;
    cin >> s;

    h.resize(n + 1);
    p.resize(n + 1);

    p[0] = 1;
    h[0] = 0;

    for (int i = 0; i < n; i++) {
        p[i + 1] = (p[i] * P) % MOD;
        h[i + 1] = (h[i] * P + (s[i] - 'a' + 1)) % MOD;
    }

    for (int i = 0; i < m; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if (solve_query(a, b, c, d)) {
            cout << 1 << "\n";
        } else {
            cout << 0 << "\n";
        }
    }

    return 0;
}
