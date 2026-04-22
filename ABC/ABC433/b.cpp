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
  vi a(n);
  rep(i, n) cin >> a[i];

  rep(i, n) {
    int res = -1;
    int min_dif = INF;
    for (int j = 0; j < i; ++j) {
      if (a[i] < a[j] && min_dif > abs(a[i] - a[j])) {
        res = j+1;
      }
    }
    if (res == INF) cout << "-1" << endl;
    else cout << res << endl;
  }
}
