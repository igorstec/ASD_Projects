//
// Created by Igor Stec on 20/10/2025.
//
#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    queue<int> traps;
    for (int i = 0; i < m; i++) {
        int t;
        cin >> t;
        traps.push(t);
    }
    if(traps.back()==n) {
        cout<<-1<<endl;
        return 0;
    }
    traps.push(n);
    vector<long long> DP(10);
    DP[0] = 0;
    vector<pair<int, int> > steps = {{1, 1}, {5, 10}, {10, 100}};


    for (int i = 1; i < n; i++) {
        while(traps.front()<i) {

            traps.pop();
        }
        int j = i % 10;
        if (traps.front() == i) {
            DP[j] = -1;
            traps.pop();
        } else {
            long long optimalVal = n * 100 + 1;
            for (pair<int, int> step: steps) {
                int k = (j + 10 - step.first) % 10;

                if (i - step.first >= 0 && DP[k] != -1 ) {
                    if (DP[k] + step.second < optimalVal) {
                        optimalVal = DP[k] + step.second;
                    }
                }
            }
            if(optimalVal == n * 100 + 1) optimalVal = -1;
            //cout<<"Manualnie: "<< i <<endl;
            DP[j] = optimalVal;

            if(j==9 && DP[j] != -1 && DP[9]-DP[0]==9) {
                int roznica = traps.front()/10*10 - i - 1;
                //cout << "roznica: " << roznica << endl;
                if(roznica > 10) {
                    DP[9]=DP[9]+roznica;
                    for(int r=0; r<9; r++) {
                        DP[r]=DP[9]-9+r;
                        //cout << "DP[" << r << "] = " << DP[r] << endl;
                    }

                    i+=roznica;
                    //cout<< "Jumping to " << i << endl;
                }
            }
        }
    }

    long long optimalVal = n * 100 + 1;
    int j=n%10;
    for (pair<int, int> step: steps) {
        int k = (j + 10 - step.first) % 10;

        if (n - step.first >= 0 && DP[k] != -1) {
            if (DP[k] + step.second < optimalVal) {
                optimalVal = DP[k] + step.second;
                break;
            }
        }
    }
    DP[j] = optimalVal;
    // //cout DP
    // for(int i=0; i<10; i++) {
    //     cout << "DP[" << i << "] = " << DP[i] << endl;
    // }

    if (DP[n % 10] == n * 100 + 1) DP[n % 10] = -1;
    cout << DP[n % 10] << endl;
    return 0;
}