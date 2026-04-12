#include <bits/stdc++.h>

using namespace std;

int main() {
  int n; cin >> n;

  int max_count = 0;

  vector<long long> l(n);
  for (int i = 0; i < n; ++i) cin >> l[i];

  for (int bit = 0; bit < (1 << n); ++bit) {
    int count = 0;
    long long pos = 1;
    for (int i = 0; i < n; ++i) {
      long long next_pos;
      if (bit & (1 << i)) {
        next_pos = pos + l[i] * 2;
      }
      else {
        next_pos = pos - l[i] * 2;
      }

      if ((pos > 0 && next_pos < 0) || (pos < 0 && next_pos > 0)) count++;
      pos = next_pos;

    }
    max_count = max(count, max_count);
  }

  cout << max_count << endl;
}
