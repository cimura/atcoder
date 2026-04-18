#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

bool ok(vector<vector<bool>> v, int r, int c, int n) {
  if (r < 0 || r + 1 >= n || c < 0 || c + 1 >= n) return false;
  bool cur = v[r][c];
  bool right = v[r][c + 1];
  bool bottom = v[r + 1][c];
  bool right_bottom = v[r + 1][c + 1];
  return (cur && right && bottom && right_bottom);
}

int main() {
  int n, m; cin >> n >> m;
  vector<vector<bool>> v(n, vector<bool>(n, true));
  rep(i, m) {
    int r, c; cin >> r >> c;
    if (ok(v, --r, --c, n)) {
      v[r][c] = false;
      v[r][c + 1] = false;
      v[r + 1][c] = false;
      v[r + 1][c + 1] = false;
    }
  }
}
