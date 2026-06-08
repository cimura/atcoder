#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>

using ll = long long;

// 実行時に変数名も表示するマクロ
#define debug(...) std::cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)

int main() {
  int h, w, k;
  cin >> h >> w >> k;
  vector<string> S(h + 1);
  vector<vector<ll>> acc(h + 1, vector<ll>(w + 1));
  rep(i, h) {
    cin >> S[i];
    rep(j, w) {
      int val = (S[i][j] == '1' ? 1 : 0);
      acc[i + 1][j + 1] = acc[i][j + 1] + acc[i + 1][j] - acc[i][j] + val;
    }
  }
  int ans = 0;
  for (int y1 = 1; y1 <= h; ++y1) {
    for (int y2 = y1; y2 <= h; ++y2) {
      for (int x1 = 1; x1 <= w; ++x1) {
        for (int x2 = x1; x2 <= w; ++x2) {
          ll current_sum = acc[y2][x2] - acc[y2][x1 - 1] - acc[y1 - 1][x2] + acc[y1 - 1][x1 - 1];
          if (current_sum == k) ans++;
        }
      }
    }
  }
  cout << ans << endl;
}
