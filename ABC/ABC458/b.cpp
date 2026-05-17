#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<double>
#define vs vector<string>
#define INF 1000000000

int main() {
  int h, w; cin >> h >> w;
  vector<vector<int>> vec(h, vector<int>(w));
  for (int y1 = 0; y1 < h; ++y1) {
    for (int x1 = 0; x1 < w; ++x1) {
      for (int y2 = 0; y2 < h; ++y2) {
        for (int x2 = 0; x2 < w; ++x2) {
          if (abs(x1 - x2) + abs(y1 - y2) == 1) {
            vec[y1][x1]++;
            //vec[y2][x2]++;
          }
        }
      }
    }
  }

  for (int y = 0; y < h; ++y) {
    for (int x = 0; x < w; ++x) {
      cout << vec[y][x] << " ";
    }
    cout << endl;
  }
}

