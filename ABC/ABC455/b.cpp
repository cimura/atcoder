#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int main() {
  int h, w; cin >> h >> w;
  vector<string> v(h);
  rep(i, h) cin >> v[i];

  int cnt = 0;
  for (int h1 = 0; h1 < h; ++h1) {
    for (int w1 = 0; w1 < w; ++w1) {
      for (int h2 = h1; h2 < h; ++h2) {
        for (int w2 = w1; w2 < w; ++w2) {
          bool ok = true;
          for (int i = h1; i <= h2; ++i) {
            for (int j = w1; j <= w2; ++j) {
              if (v[i][j] != v[h1 + h2 -i][w1 + w2 -j]) {
                ok = false;
                break;
              }
            }
          }
          if (ok) cnt++;
        }
      }
    }
  }
  cout << cnt << endl;
}

