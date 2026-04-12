#include <iostream>
#include <iomanip>
#include <cmath>
#include <numbers>
#include <bits/stdc++.h>

using namespace std;

int main() {
  int t, x; cin >> t >> x;

  vector<pair<int, int> > p;
  int prev = 0;
  for (int i = 0; i <= t; ++i) {
    int now;
    cin >> now;

    if (i == 0) {
      p.push_back({ i,now });
      prev = now;
    }
    else if (abs(now - prev) >= x) {
      prev = now;
      p.push_back({ i, now });
    }
  }

  for (auto a : p) {
    cout << a.first << " " << a.second << endl;
  }
}
