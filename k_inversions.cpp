//
// Created by Igor Stec on 10/11/2025.
//

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <set>

using namespace std;

#define MOD 1000000000

int recurency(int index, int remainingK, vector<set<int> > &dp) {
    if (dp[index].empty() && remainingK > 0) return 0;
    if (remainingK == 0) return 1;

    int wynik = 0;
    for (int next: dp[index]) {
        wynik = (wynik + recurency(next, remainingK - 1, dp))%MOD;
    }
    return wynik % MOD;
}


int main() {
    int n, k;
    cin >> n >> k;
    int wynik = 0;
    vector dp(n, set<int>());
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[i]) {
                dp[j].insert(i);
            }
        }
    }
    //cout dp
    // for (int i = 0; i < n; i++) {
    //     cout << "dp[" << i << "]: ";
    //     for (int next: dp[i]) {
    //         cout << next << " ";
    //     }
    //     cout << endl;
    // }

    for (int i = 0; i < n - k+1; i++) {
        wynik = (wynik + recurency(i, k-1, dp)) % MOD;
    }
    cout << wynik << endl;
    return 0;
}
