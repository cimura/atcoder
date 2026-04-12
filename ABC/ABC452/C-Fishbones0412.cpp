#include <bits/stdc++.h>

using namespace std;
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int main() {
  int n; cin >> n;
  vi a(n), b(n);
  rep(i, n) {
    cin >> a[i] >> b[i];
    b[i]--;
  }

  int m; cin >> m;
  vs vm(m);
  rep(i, m) {
    cin >> vm[i];
  }

  set<tuple<int, int, char>> s_tuple;

  // 前計算
  // 長さ、文字目、文字
  rep(i, m) {
    int len = vm[i].size();
    rep(j, len) {
      s_tuple.emplace(len, j, vm[i][j]);
    }
  }

  rep(j, m) {
    bool ok = true;
    if (vm[j].size() != n) ok = false;
    if (ok) {
      rep(i, n) {
        if (!s_tuple.count(tie(a[i], b[i], vm[j][i]))) ok = false;
      }
    }
    if (ok) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  }
}
