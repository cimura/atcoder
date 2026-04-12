#include <bits/stdc++.h>

using namespace std;
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int main() {
  int n, m; cin >> n >> m;

  vi vm(m);
  rep(i, m) {
    vm[i] = i + 1;
  }

  rep(i, n) {
    int l; cin >> l;
    rep(j, l) {
      int x; cin >> x;
      auto pos = find(vm.begin(), vm.end(), x);
      if (pos != vm.end() && *pos != -1) {
        cout << *pos << endl;
        *pos = -1;
        break;
      }
      else if (j == l - 1 && pos == vm.end()) {
        cout << "0" << endl;
        break;
      }
    }
  }
}
