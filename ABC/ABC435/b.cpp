#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

using ll = long long;

int main() {
  int n; cin >> n;
  vi a(n);
  rep(i, n) cin >> a[i];
  int count = 0;
  for (int l = 0; l < n; ++l) {
    for (int r = l; r < n; ++r) {
      int sum = accumulate(a.begin() + l, a.begin() + r + 1, 0);
      //cout << "sum: " << sum << endl;
      int div_ok = false;
      for (int i = l; i <= r; ++i) {
        if (sum % a[i] == 0) {
          div_ok = true;
          break;
        }
      }
      if (!div_ok) count++;
    }
  }
  cout << count << endl;
}
