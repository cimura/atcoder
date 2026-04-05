#include <bits/stdc++.h>

using namespace std;

/**
 * dp[i] = dp[i-j]+min(i-jに行くためのコスト);
 *
 */

 //int main() {
 //  int N, K; cin >> N >> K;

 //  const long long INF = 10e7;
 //  vector<int> dp(N, INF);
 //  vector<int> h(N);
 //  dp[0] = 0;
 //  for (int i = 0; i < N; ++i) cin >> h[i];

 //  for (int i = 0; i < N; ++i) {
 //    // iに行くまでのコストを計算
 //    for (int j = 1; j <= K; ++j) {
 //      if (i - j >= 0) {
 //        dp[i] = min(dp[i], dp[i - j] + abs(h[i] - h[i - j]));
 //      }
 //    }
 //  }
 //  cout << dp[N - 1] << endl;
 //}

int main() {
  int N, K; cin >> N >> K;

  const long long INF = 10e10;
  vector<int> dp(N, INF);
  vector<int> h(N);
  dp[0] = 0;
  for (int i = 0; i < N; ++i) cin >> h[i];

  for (int i = 0; i < N; ++i) {
    // iに行くまでのコストを計算
    for (int j = 1; j <= K; ++j) {
      if (i + j < N) {
        dp[i + j] = min(dp[i + j], dp[i] + abs(h[i+j] - h[i]));
      }
    }
  }
  cout << dp[N - 1] << endl;
}

