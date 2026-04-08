#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, l, r; cin >> n >> l >> r;
  string s; cin >> s;
  int count = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i + l; j < n; ++j) {
      if (s[j] == s[i] && (j - i) <= r) {
        count++;
        //cout << "i: " << i << ", j: " << j << endl;
      }
    }
  }
  cout << count << endl;
}
