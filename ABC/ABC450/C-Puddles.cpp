#include <iostream>

using namespace std;
#define SIZE 1000

// bfsを使おう

int main() {
  int h, w;
  cin >> h >> w;

  bool found;
  char map[SIZE][SIZE] = { 0 };
  int count = 0;

  for (int y = 0; y < h; ++y) {
    for (int x = 0; x < w; ++x) {
      cin >> map[x][y];
    }
  }

  for (int y = 0; y < h; ++y) {
    found = false;
    for (int x = 0; x < w; ++x) {
      if (x == 0 || y == 0 || x == w - 1 || y == h - 1) continue;
      if (!found && map[x][y] == '.') found = true;
      else if (found && map[x][y] == '.') {
        cout << "x: " << x << ", y: " << y << endl;
        count++;
        break;
      }
    }
  }
  cout << count << endl;
}
