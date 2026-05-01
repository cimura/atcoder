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

  int l = 0;
  int r = n - 1;
  rep(i, n) {
    if (r <= l) {
      cout << 0 << endl;
      return 0; 
    }
    if (a[l] == 0) l++;
    if (a[r] == 0) r--;
  }
  cout << r - l << endl;
}
