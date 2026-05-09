#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<double>
#define vs vector<string>
#define INF 1000000000

int main() {
  int n; cin >> n;
  vector<vector<int>> v(n);
  rep(i, n) {
    int l; cin >> l;
    vi a(l);
    rep(j, l) {
      cin >> a[j];
    }
    v[i] = a;
  }
  int x, y; cin >> x >> y;
  cout << v[x-1][y-1] << endl;
}

