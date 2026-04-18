#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int main() {
  int n, m; cin >> n >> m;
  vector<vector<int>> to(n);
  rep(i, m) {
    int a, b;
    cin >> a >> b;
    a--; b--;
    to[a].push_back(b);
  }

  vector<bool> visited(n);
  queue<int> q;
  visited[0] = true; q.push(0);
  while (q.size()) {
    int v = q.front(); q.pop();
    for (int u : to[v]) {
      if (visited[u]) continue;
      q.push(u);
      visited[u] = true;
    }
  }
  int ans = 0;
  rep(i, n) if (visited[i]) ans++;
  cout << ans << endl;
}
