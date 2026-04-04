#include <iostream>

using namespace std;

int main() {
  int n;
  cin >> n;

  for (int i = n; i > 0; --i) {
    if (i == n) {
      cout << i;
    }
    else {
      cout << "," << i;
    }
  }
  cout << endl;
}
