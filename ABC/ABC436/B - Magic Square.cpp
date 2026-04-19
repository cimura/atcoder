#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int main() {
  int n; cin >> n;
  vector<vector<int>> v(n, vector<int>(n));

  int k = 1;
  int r = 0, c = (n - 1) / 2;
  rep(i, n * n) {
    v[r][c] = k;
    int nr = (r - 1 + n) % n;
    int nc = (c + 1) % n;
    if (v[nr][nc] != 0) {
      nr = (r + 1) % n;
      nc = c;
    }
    r = nr;
    c = nc;
    k++;
  }

  rep(i, n) {
    rep(j, n) {
      cout << v[i][j] << " ";
    }
    cout << endl;
  }
}
