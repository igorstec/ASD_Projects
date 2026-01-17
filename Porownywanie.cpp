#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
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

bool is_zblizone(string &s1, string &s2) {
    bool to_return = false;
    if (s1 == s2) return true;
    int s1l = static_cast<int>(s1.size()), s2l = static_cast<int>(s2.size());
    if (std::abs(s1l - s2l) >= 2)
        return false;
    if (s1l == s2l) {
        for (int i = 0; i < s1l; i++) {
            if (s1[i] != s2[i]) {
                if (to_return == false) {
                    to_return = true;
                } else {
                    return false;
                }
            }
        }
        return to_return;
    }
    if (s1l < s2l) {
        swap(s1, s2);
    }
    //s1 wiekszy
    int i = 0;
    while (i < s2l && s1[i] == s2[i]) {
        i++;
    }
    if (i == s2l)
        return true;
    string sub1 = s1.substr(i + 1, s1l - i - 1);
    string sub2 = s2.substr(i, s2l - i);
    if (sub1 == sub2) { return true; }
    return false;
}

bool solve_query(int i, int b, int c, int d) {
    return false;
};

int main() {
    // Optymalizacja I/O
    ios_base::sync_with_stdio(false);
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
