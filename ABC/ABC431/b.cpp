#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

using ll = long long;

int main() {
  int x, n; cin >> x >> n;
  vector<pair<int, bool>> w(n);
  rep(i, n) {
    int ww; cin >> ww;
    w[i] = { ww, false };
  }
  int q; cin >> q;

  int ans = x;
  rep(i, q) {
    int p; cin >> p;
    --p;
    if (!w[p].second) {
      w[p].second = true;
      ans += w[p].first;
    } else {
      w[p].second = false;
      ans -= w[p].first;
    }
    cout << ans << endl;
  }
}
