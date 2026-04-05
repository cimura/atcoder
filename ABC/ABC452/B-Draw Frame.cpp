#include <iostream>
#include <iomanip>
#include <cmath>
#include <numbers>

using namespace std;

int main() {
  int h, w;
  cin >> h >> w;
  for (int y = 0; y < h; ++y) {
    for (int x = 0; x < w; ++x) {
      if (x == 0 || y == 0 || x == w - 1 || y == h - 1) {
        cout << "#";
      } else {
        cout << ".";
      }
    }
    cout << endl;
  }
}
