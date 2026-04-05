#include <bits/stdc++.h>

using namespace std;

int main() {
  int H, W; cin >> H >> W;
  vector<char> v(H * W);
  for (int y = 0; y < H; ++y) {
    string s; cin >> s;
    for (int i = 0; i < s.length(); ++i) {
      v[y * W + i] = s[i];
    }
  }

  int count = 0;
  for (int y = 0; y < H; ++y) {
    for (int x = 0; x < W; ++x) {
      for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
          if (dy == 0 && dx == 0) continue;
          int ny = y + dy;
          int nx = x + dx;
          int idx = ny * W + nx;
          if (idx >= 0 && idx < H * W) {
            v[idx] = '#';
          }
        }
      }
      int dot = std::count(v.begin(), v.end(), '.');
      if (dot == 0) break;
      count++;
    }
  }
  cout << count << endl;
}
