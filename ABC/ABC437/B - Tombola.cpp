#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int main() {
  int h,w,n; cin >> h >> w >> n;
  vector<vector<int>> v(h, vector<int>(w, 0));

  rep(i, h) {
    rep(j, w) {
      cin >> v[i][j];
    }
  }
  vi b(n);
  rep(i, n) cin >> b[i];

  int max_count = INT_MIN;
  rep(i, h) {
    int cnt = 0;
    rep(j, w) {
      if (find(b.begin(), b.end(), v[i][j]) != b.end()) {
        cnt++;
      }
    }
    max_count = max(cnt, max_count);
  }
  cout << max_count << endl;
}
