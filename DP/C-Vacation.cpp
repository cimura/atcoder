#include <bits/stdc++.h>

using namespace std;

int max3(int a, int b, int c) {
  int m = a;
  if (m < b) m = b;
  if (m < c) m = c;
  return m;
}

int main() {
  int n; cin >> n;
  vector<long long> h(n);

  if (n == 1) {
    int a, b, c; cin >> a >> b >> c;
    cout << max3 << endl; return 0;
  }

  for (int i = 0; i < n; ++i) {
    int a, b, c; cin >> a >> b >> c;
    int selected = 0;
    // 前回maxで選んだやつは選びたくない
    if (i > 0) {
      selected = max3(a, b, c);
      h[i] = max(h[i], h[i - 1] + selected);
    }
  }
  cout << h[n - 1] << endl;
}
