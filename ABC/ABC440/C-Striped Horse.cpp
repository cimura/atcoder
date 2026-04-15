#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int main() {
  int t; cin >> t;
  rep(i, t) {
    int n, w; cin >> n >> w;
    vi c(n);
    rep(l, n) {
      cin >> c[l];
    }
    long long min_cost = LLONG_MAX;
    rep(j, n) {
      long long cost = 0;
      rep(k, min(n, 2 * w)) {
        int mod = (j + k) % (2 * w);
        if (mod < w) cost += c[k];
      }
      min_cost = min(min_cost, cost);
    }
    cout << min_cost << endl;
  }
}
