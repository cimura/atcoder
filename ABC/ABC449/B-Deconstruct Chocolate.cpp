#include <bits/stdc++.h>

using namespace std;

int main() {
  int h, w, q; cin >> h >> w >> q;
  vector<vector<int>> v(h + 1, vector<int>(w + 1, 1));
  for (int i = 0; i < q; ++i) {
    int type, query; cin >> type >> query;
    int count = 0;
    if (type == 1) {
      for (int y = h - 1; y >= h - query; --y) {
        for (int x = 0; x < w; ++x) {
          if (v[y][x]) count++;
          v[y][x] = 0;
        }
      }
      h = h - query;
    }
    else {
      for (int y = 0; y < h; ++y) {
        for (int x = w - 1; x >= w - query; --x) {
          if (v[y][x]) count++;
          v[y][x] = 0;
        }
      }
      w = w - query;
    }
    cout << count << endl;
  }
}
