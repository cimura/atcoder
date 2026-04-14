#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int main() {
  int n, k, x; cin >> n >> k >> x;
  vi a(n);
  rep(i, n) cin >> a[i];

  sort(a.rbegin(), a.rend());
  long long drunk = 0;
  for (int i = n - k; i < n; ++i) {
    drunk += a[i];
    if (drunk >= x) {
      cout << i + 1 << endl;
      return 0;
    }
  }
  cout << -1 << endl;
}
