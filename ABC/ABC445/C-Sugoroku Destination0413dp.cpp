#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int solve(vi& a, int idx, vi& dp) {
  if (dp[idx] != 0) return dp[idx];
  if (idx == a[idx - 1]) {
    return dp[idx] = idx;
  }
  return dp[idx] = solve(a, a[idx - 1], dp);
}

int main() {
  int n; cin >> n;
  vi dp(n + 1, 0);
  vi a(n + 1);
  rep(i, n) cin >> a[i];

  rep(i, n) {
    if (i != 0) cout << " ";
    cout << solve(a, i + 1, dp);
  }
  cout << endl;
}
