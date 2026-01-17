#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
using namespace std;

bool is_zblizone(string &s1, string &s2) {
    bool to_return = false;
    if (s1 == s2) return true;
    int s1l = static_cast<int>(s1.size()), s2l = static_cast<int>(s2.size());
    if (std::abs( s1l - s2l) >= 2)
        return false;
    if(s1l==s2l) {
        for(int i = 0; i<s1l; i++) {
            if(s1[i]!=s2[i]) {
                if(to_return==false) {
                    to_return=true;
                }else {
                    return false;
                }
            }
        }
    }else {
        if(s1l<s2l) {
            swap(s1, s2);
        }
        //s1 wiekszy
        int i=0;
        while(i<s2l && s1[i]==s2[i])
            i++;
        if(i==s2l)return true;
        string sub1 = s1.substr(i+1, s1l-i-1);
        string sub2 = s2.substr(i, s2l-i);
        if(sub1==sub2){return true;}
        return false;
    }


    return to_return;
}

int main() {
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    for (int i = 0; i < m; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        string sub1 = s.substr(a - 1, b - a + 1);
        string sub2 = s.substr(c - 1, d - c + 1);
        if(is_zblizone(sub1, sub2)) {
            cout<<1<<'\n';
        }else {
            cout<<0<<'\n';
        }
    }


    return 0;
}
