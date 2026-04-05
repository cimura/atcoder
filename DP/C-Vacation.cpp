#include <bits/stdc++.h>

using namespace std;

int max3(int a, int b, int c) {
  int m = a;
  if (m < b) m = b;
  if (m < c) m = c;
  return m;
}

int main() {
  int n; cin >> n;
  vector<vector<long long>> dp(n, vector<long long>(3, 0));

  int a, b, c;
  cin >> a >> b >> c;
  dp[0][0] = a;
  dp[0][1] = b;
  dp[0][2] = c;

  for (int i = 1; i < n; ++i) {
    cin >> a >> b >> c;
    dp[i][0] = max(dp[i - 1][1] + a, dp[i - 1][2] + a);
    dp[i][1] = max(dp[i - 1][0] + b, dp[i - 1][2] + b);
    dp[i][2] = max(dp[i - 1][0] + c, dp[i - 1][1] + c);
  }
  cout << max3(dp[n - 1][0], dp[n - 1][1], dp[n - 1][2]) << endl;
}
