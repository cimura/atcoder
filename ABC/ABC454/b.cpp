#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int main() {
  int n, m; cin >> n >> m;
  vi f(n);
  rep(i, n) cin >> f[i];
  bool dif = true;
  rep(i, m) {
    if (count(f.begin(), f.end(), i) > 1) {
      dif = false;
      break;
    }
  }

  if (dif) cout << "Yes" << endl;
  else cout << "No" << endl;

  for (int i = 1; i <= m; ++i) {
    if (find(f.begin(), f.end(), i) != f.end()) {
    }
    else {
      cout << "No" << endl;
      return 0;
    }
  }
  cout << "Yes" << endl;
}
