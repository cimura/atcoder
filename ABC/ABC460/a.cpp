#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int main() {
  int n, m; cin >> n >> m;
  int ans = 0;
  int x = 1;
  while (x > 0) {
    x = n % m;
    m = x;
    ans++;
  }
  cout << ans << endl;
}
