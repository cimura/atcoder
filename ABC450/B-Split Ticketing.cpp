#include <iostream>
#include <vector>

using namespace std;

#define SIZE 105

int main() {
  int n;
  cin >> n;

  int v[SIZE][SIZE] = { 0 };

  //cout << endl << endl;
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      int c;
      cin >> c;
      v[i][j] = c;
      //cout << c << " ";
    }
    //cout << endl;
  }

  for (int a = 1; a <= n; ++a) {
    for (int b = a + 1; b <= n; ++b) {
      for (int c = b + 1; c <= n; ++c) {
        if (v[a][b] + v[b][c] < v[a][c]) {
          cout << "Yes" << endl;
          return 0;
        }
      }
    }
  }
  cout << "No" << endl;
  return 0;
}
