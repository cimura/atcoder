#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

using ll = long long;

// 到達可能な点はBFSで解ける

int main() {
  int n, m; cin >> n >> m;
  vector<vector<int>> to(n);
  rep(i, m) {
    int a, b;
    cin >> a >> b;
    --a; --b;
    to[b].push_back(a);
  }
  int q; cin >> q;
  vector<bool> black(n);
  rep(i, q) {
    int type, v;
    cin >> type >> v;
    --v;
    if (type == 1) {
      queue<int> q;
      auto push = [&](int v) {
        if (black[v]) return;
        black[v] = true;
        q.push(v);
        };
      push(v);
      while (q.size()) {
        int v = q.front(); q.pop();
        for (int u: to[v]) push(u);
      }
    }
    else {
      if (black[v]) cout << "Yes\n";
      else cout << "No\n";
    }
  }
}
