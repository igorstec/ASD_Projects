#include <iostream>

using namespace std;
int main() {
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);
  int n, m, to_return = 0;
  cin >> n >> m;

  for(int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    //TODO: implement
    to_return = max(to_return, c);
    }

    cout << to_return << endl;
    return 0;
}