#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

using ll = long long;

int main() {
  int n; cin >> n;
  vi a(n + 1);
  rep(i, n) cin >> a[i + 1];

  vector<int> found(n + 1, 0);
  vector<int> path;

  // スタートの頂点
  int v = 1;
  while (found[v] == 0) {
    found[v] = 1;
    path.push_back(v);
    v = a[v];
  }
  vector<int> ans;
  bool in_cycle = false;
  for (int p : path) {
    if (p == v) in_cycle = true;
    if (in_cycle) ans.push_back(p);
  }
  cout << ans.size() << endl;
  for (int aa : ans) cout << aa << " ";
  cout << endl;
}
