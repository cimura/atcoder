#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, m; cin >> n >> m;
  vector<int> c(m);
  for (int i = 0; i < m; ++i) cin >> c[i];

  int total = 0;
  for (int i = 0; i < n; ++i) {
    int a, b; cin >> a >> b;
    if (b <= c[a - 1]) {
      c[a - 1] -= b;
      total += b;
    }
    else {
      total += c[a - 1];
      c[a - 1] = 0;
    }
  }
  cout << total << endl;
}
