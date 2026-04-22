#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

using ll = long long;

void solve() {
  int n, h; cin >> n >> h;
  int top = h, bottom = h;
  int now = 0;
  bool ok = true;
  rep(i, n) {
    int t, l, u;
    cin >> t >> l >> u;
		top += (t - now);
    bottom -= (t - now);

    if (l > top || u < bottom) ok = false;
    top = min(top, u);
    bottom = max(bottom, l);
    now = t;
  }
  if (ok) cout << "Yes\n";
  else cout << "No\n";
}

int main() {
  int t; cin >> t;
  while (t--) {
    solve();
  }
}
