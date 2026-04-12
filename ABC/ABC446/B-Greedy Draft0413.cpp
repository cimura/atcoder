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

    vector<bool> is_used(m + 1, false);
  rep(i, n) {
    int l; cin >> l;
    int found_val = 0;
    rep(j, l) {
      int x; cin >> x;
      if (found_val == 0 && !is_used[x]) {
        found_val = x;
        is_used[x] = true;
      }
    }
    cout << found_val << endl;
  }
}
