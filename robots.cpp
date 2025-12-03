#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_N = 200000;
const int MAX_M = 1e9;

int main() {
    int n,m;
    cin >> n >> m;
    vector<int> robots(n);
    vector<int> dest(n);
    for (int i = 0; i < n; i++) {
        cin >> robots[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> dest[i];
    }
    //sort robots and dest
    sort(robots.begin(), robots.end());
    sort(dest.begin(), dest.end());

    vector<int> DP(n, 0 );
    int robot=0;
    int destination=0;
    int index_szuk=0;
    int index=0; //index destynacji
    int maxDP=0;
    int result=0;

    //int bylo=0;
    //int result0=0;
    // while(dest[destination]>robots[robot] && robot<n) {
    //     robot++;
    // }
    // robot = robot < n ? robot : 0;
    // index_szuk = robot;
    // //cout<< "Starting pair: " << " Dest: " << dest[0] << " Robot: " << robots[index_szuk] << "\n";
    //
    //
    // while(bylo < n) {
    //     result0+= min(abs(robots[index_szuk] - dest[index]), m - abs(robots[index_szuk] - dest[index]));
    //             //cout<< " Result before: " << result << "\n";
    //             index = (index + 1) % n; // kolejna destynacja ktorej trzeba znalezc pare
    //             index_szuk = (index_szuk + 1) % n; // kolejny robot do parowania
    //             bylo++;
    //
    //             //cout<< " Dest: " << dest[index] << " Robot: " << robots[index_szuk] << " Result after: " << result0 << "\n";
    //
    // }
    // index_szuk = (robot - 1 + n) % n;
    // bylo=0;
    // index = 0;
    // //cout<< "Starting pair reverse: " << " Dest: " << dest[0] << " Robot: " << robots[index_szuk] << "\n";
    // while(bylo < n) {
    //     result+= min(abs(robots[index_szuk] - dest[index]), m - abs(robots[index_szuk] - dest[index]));
    //
    //             //cout<< " Result before: " << result << "\n";
    //             index = (index - 1 + n) % n; // kolejna destynacja ktorej trzeba znalezc pare
    //             index_szuk = (index_szuk - 1 + n) % n; // kolejny robot do parowania
    //             bylo++;
    //
    //             //cout<< " Dest: " << dest[index] << " Robot: " << robots[index_szuk] << " Result after: " << result << "\n";
    //
    //
    // }
    // //cout<<"Result0: " << result0 << "\n";
    // //cout<<"Result: " << result << "\n";
    // cout<<result<<"."<<result0;
    // result = min(result, result0);
    // cout<< result << "\n";
    // return 0;




     // while(true) {
     //     while(dest[destination]>robots[robot] && robot<n) {
     //             robot++;
     //         }
     //     robot = robot < n ? robot : 0;
     //     int right_am=0;
     //     if(destination > robot) {
     //         right_am = m - dest[destination] + robots[0];
     //     }else {
     //         right_am = abs(dest[destination]-robots[robot]);
     //     }
     //     int left_am = abs(dest[destination]-robots[(robot-1+n)% n]);
     //
     //     DP[destination] = abs(left_am - right_am);
     //
     //     // cout<< "Dest: " << dest[destination] << " Robot right: " << robots[robot] << " Robot left: " << robots[(robot-1+n)% n] <<
     //     //     " Left am: " << left_am << " Right am: " << right_am << " DP: " << DP[destination] << "\n";
     //
     //     if(DP[destination]>maxDP) {
     //         maxDP=DP[destination];
     //         index=destination;
     //         if(left_am<right_am) {
     //             index_szuk = (robot-1+n)% n;
     //             result= left_am;
     //         }else {
     //             index_szuk = robot;
     //             result= right_am;
     //         }
     //     }
     //     destination++;
     //     if(destination==n) {
     //         break;
     //     }
     // }
     // for(int i=0;i<n;i++) {
     //     cout << DP[i] << " ";
     // }
     // cout << "\n";
     // cout<< maxDP << " " << index << " " << index_szuk << "\n";
    // int bylo=1;
    //
    //
    //
    //  if(index>index_szuk) {//jesli destynacja wiekszy index to do przodu od destynacji parujemy
    //      while(bylo<n) {
    //          //cout<< " Result before: " << result << "\n";
    //          index = (index + 1) % n; // kolejna destynacja ktorej trzeba znalezc pare
    //          index_szuk = (index_szuk + 1) % n; // kolejny robot do parowania
    //          bylo++;
    //          result+= min(abs(robots[index_szuk] - dest[index]), m - abs(robots[index_szuk] - dest[index]));
    //          //cout<< " Dest: " << dest[index] << " Robot: " << robots[index_szuk] << " Result after: " << result << "\n";
    //      }
    //  }else {
    //      while(bylo<n) {
    //          //cout<< " Result before: " << result << "\n";
    //          index = (index - 1 + n) % n; // kolejna destynacja ktorej trzeba znalezc pare
    //          index_szuk = (index_szuk - 1 + n) % n; // kolejny robot do parowania
    //          bylo++;
    //          result+= min(abs(robots[index_szuk] - dest[index]), m - abs(robots[index_szuk] - dest[index]));
    //          //cout<< " Dest: " << dest[index] << " Robot: " << robots[index_szuk] << " Result after: " << result << "\n";
    //      }
    //  }



    cout<< result << "\n";

    return 0;
}
