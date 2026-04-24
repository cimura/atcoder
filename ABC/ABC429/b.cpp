#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

using ll = long long;

int main() {
  int n, m; cin >> n >> m;
  vi a(n);
  int sum = 0;
  rep(i, n) {
    cin >> a[i];
    sum += a[i];
  }

  rep(i, n) {
    if (sum - a[i] == m) {
      cout << "Yes" << endl;
      return 0;
    }
  }
  cout << "No" << endl;
}
