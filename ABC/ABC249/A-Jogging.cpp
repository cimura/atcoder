#include <bits/stdc++.h>

using namespace std;

int main() {
  int a, b, c, d, e, f, x; cin >> a >> b >> c >> d >> e >> f >> x;
  int aoki = 0, taka = 0;

  int time = x;
  while (x >= 0) {
    int s = a;
    if (a > x) s = x;
    taka += s * b;
    x -= (a + c);
  }

  x = time;

  while (x >= 0) {
    int s = d;
    if (d > x) s = x;

    aoki += s * e;
    x -= (d + f);
  }

  //cout << "Aoki: " << aoki << endl;
  //cout << "Takahashi: " << taka << endl;

  if (aoki > taka) {
    cout << "Aoki" << endl;
  }
  else if (aoki < taka) {
    cout << "Takahashi" << endl;
  }
  else {
    cout << "Draw" << endl;
  }
}
