#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

using ll = long long;

int main() {
  ll n, x, y; cin >> n >> x >> y;
  vll a(n);
  rep(i, n) cin >> a[i];
  sort(a.begin(), a.end());

  ll w = a[0] * y;
  ll ans = 0;
  rep(i, n) {
    ll sw = a[i] * y;
    ll dif = sw - w;
    if (dif % (y - x) != 0) {
      cout << "-1" << endl;
      return 0;
    }
    //cout << "dif: " << dif << endl;
    ll num = dif / (y - x);
    if (num > a[i]) {
      cout << "-1" << endl;
      return 0;
    }
    ans += a[i] - num;
  }
  cout << ans << endl;
}
