#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, m; cin >> n >> m;
  vector<long long> v(n + 1, 0);
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b;
    v[a] += 1;
    v[b] += 1;
  }

  for (int j = 0; j < n; ++j) {
    // (n - v[j] - 1) C 3
    long long cand = n - v[j + 1] - 1;

    string result = "";
    if (cand < 3) result += "0";
    else {
      result += to_string((cand * (cand - 1) * (cand - 2)) / (3 * 2 * 1));
    }
    if (j != n - 1) result += " ";
    cout << result;
  }
  cout << endl;
}
