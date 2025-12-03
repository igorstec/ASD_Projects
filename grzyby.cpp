#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> x(n), y(n);

    // Wczytaj pozycje robotów
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    // Wczytaj pozycje celów
    for (int i = 0; i < n; i++) {
        cin >> y[i];
    }

    // Sortuj obie tablice
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());

    vector<long long> sums(2*n+1, 0);
    vector<int> z(3*n);
    vector<int> pierwszy_z_wiekszy_od_x(n);
    vector<int> pierwszy_x_mniejszy_od_z(3*n);



    for(int i=0;i<n;i++) {
        z[i]=y[i]-m; // pelne liczby bez 0
        z[i+n]=y[i];
        z[i+2*n]=y[i]+m;
    }

    int j=n-1;
    for(int i=0;i<n;i++) { // pierwdzy z wiekszy lub rowny x
        while(j< 3*n && z[j] <= x[i]) {
            j++;
        }
        pierwszy_z_wiekszy_od_x[i]=j;
    }
    j=0;
    for(int i=n;i<2*n;i++) {
        while(j < n && z[i] > x[j]) {
            j++;
        }
        pierwszy_x_mniejszy_od_z[i]=j;
    }


    for(int i=0;i<n;i++) {
        sums[0]+=x[i];
        sums[pierwszy_z_wiekszy_od_x[i]-i]-=2*x[i];
    }

    for(int i=3*n-1;i>=2*n;i--) {
        sums[i-n+1]+=z[i];
    }
    for(int i=2*n-1;i>=n;i--) {
        sums[i-n+1]-=z[i];
        sums[i - pierwszy_x_mniejszy_od_z[i] + 1]+=2*z[i];
        sums[i+1]-=z[i];
    }
    for(int i=n-1;i>=0;i--) {
        //dla akzdego z
        sums[0]-=z[i];
        sums[i+1]+=z[i];
    }


    long long min_ans = LLONG_MAX;

    for(int i=0;i<2*n+1;i++) {
        if(i>0) {
            sums[i]+=sums[i-1];
        }
        if(sums[i]<min_ans) {
            min_ans=sums[i];
        }
    }
    cout<< min_ans << "\n";
    return 0;
}
