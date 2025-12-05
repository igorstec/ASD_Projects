#include <iostream>
#include <math.h>
#include <vector>
#include <unistd.h>

using namespace std;


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin>>n >> m;
    vector<int> stock_index(n);
    for(int i=0; i<n; i++){
        cin>>stock_index[i];
    }
    //Process data
    for(int i=0; i<m; i++){
        int s,e,l,h;
        cin>>s>>e>>l>>h;
        int Q_query=0;
        int C_query=0;
        //Check C and Q query
        cout<<Q_query<<" "<<C_query<<"\n";
    }

    return 0;
}
