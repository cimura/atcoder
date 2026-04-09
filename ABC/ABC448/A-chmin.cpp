#include <iostream>
#include <iomanip>
#include <cmath>
#include <numbers>

using namespace std;

int main() {
  int n, x;
  cin >> n >> x;
  for (int i = 0; i < n; ++i) {
    int a; cin >> a;
    if (a < x) {
      cout << 1 << endl;
      x = a;
    }
    else cout << 0 << endl;
  }
}
