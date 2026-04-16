#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int main() {
  int h,w,n; cin >> h >> w >> n;
  vector<vector<int>> v(h, vector<int>());

  rep(i, h) {
    rep(j, w) {
      cin >> v[i][j];
    }
  }
  vi b(n);
  rep(i, n) cin >> b[i];

  int min_count = INT_MAX;
  rep(i, h) {
    int cnt = 0;
    rep(j, w) {
      if (find(b.begin(), b.end(), v[i][j]) != b.end()) {
        cnt++;
      }
    }
    min_count = min(cnt, min_count);
  }
  cout << min_count << endl;
}
