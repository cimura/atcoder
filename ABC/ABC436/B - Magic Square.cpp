#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int main() {
  int n; cin >> n;
  vector<vector<int>> v(n, vector<int>(n, 0));

  int k = 1;
  v[0][(n - 1) / 2] = k;
  int x = 0, y = (n - 1) / 2;
  rep(i, n * n - 1) {
    if (v[(x - 1) % n][(y + 1) % n] == 0) {
      v[(x - 1) % n][(y + 1) % n] = 1;
    } else {
      v[(x + 1) % n][y] = k + 1;
    }
  }

  rep(i, n) {
    rep(j, n) {
      cout << v[i][j] << " ";
    }
    cout << endl;
  }
}
