#include <bits/stdc++.h>

using namespace std;

int main() {
  int h, w, q; cin >> h >> w >> q;
  vector<vector<int>> v(h + 1, vector<int>(w + 1, 1));
  for (int i = 0; i < q; ++i) {
    int type, query; cin >> type >> query;
    int count = 0;
    if (type == 1) {
      for (int y = 0; y < query; ++y) {
        for (int x = 0; x < w; ++x) {
          if (v[y][x]) count++;
          v[y][x] = 0;
        }
      }
      cout << count << endl;
    }
    else {
      for (int y = 0; y < h; ++y) {
        for (int x = 0; x < query; ++x) {
          if (v[y][x]) count++;
          v[y][x] = 0;
        }
      }
      cout << count << endl;
    }
  }
}
