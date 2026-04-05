#include <bits/stdc++.h>

using namespace std;

int main() {
  int N; cin >> N;

  vector<int> dp(N);
  int h[N];
  for (int i = 0; i < N; ++i) cin >> h[i];

  dp[0] = 0;
  dp[1] = abs(h[1] - h[0]);

  for (int i = 2; i < N; ++i) {
    dp[i] = min(dp[i - 2] + abs(h[i] - h[i - 2]), dp[i - 1] + abs(h[i] - h[i - 1]));
    cout << "dp[" << i << "]: " << dp[i] << endl;
  }
  cout << dp[N - 1] << endl;
}
