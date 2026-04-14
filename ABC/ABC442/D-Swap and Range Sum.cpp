#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

/**
 * 1 2 [3] [4] 5 6 7 8 9 10
 * 1 2 [4] [3] 5 6 7 8 9 10
 * 1 3 <6>  10 15 21 28 36 45 55
 *
 */

int main() {
  int n, q; cin >> n >> q;
  vi a(n), sum(n + 1);
  rep(i, n) cin >> a[i];

  sum[0] = a[0];
  for (int i = 1; i < n; ++i) {
    sum[i] = a[i] + sum[i - 1];
  }

  //for (auto t : sum) cout << t << " ";
  //cout << endl;
  //cout << "**********************" << endl;

  rep(i, q) {
    int type; cin >> type;
    if (type == 1) {
      int x; cin >> x;
      //cout << "swap " << a[x - 1] << " and " << a[x] << endl;
      swap(a[x - 1], a[x]);
      sum[x - 1] = sum[x] - a[x];
    }
    else if (type == 2) {
      int l, r; cin >> l >> r;
      //for (auto t : a) cout << t << " ";
      //cout << endl;
      //cout << "**********************" << endl;
      //for (auto t : sum) cout << t << " ";
      //cout << endl;
      //cout << "type2   l: " << l << ", r: " << r << endl;
      if (l <= 1) cout << sum[r - 1] << endl;
      else cout << sum[r - 1] - sum[l - 2] << endl;
    }
  }
}
