#include <bits/stdc++.h>

using namespace std;

int main() {
  int n; cin >> n;

  int count = 0;
  double pos = 0.5;
  for (int i = 0; i < n; ++i) {
    long long l; cin >> l;
    if (pos > 0) {
      pos -= l;
      //cout << "POS: " << pos << endl;
      if (pos < 0) count++;
    } else {
      pos += l;
      //cout << "POS: " << pos << endl;
      if (pos > 0) count++;
    }
  }

  cout << count << endl;
}
