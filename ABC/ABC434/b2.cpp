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
  vi a(n), b(n);
  rep(i, n) {
    cin >> a[i] >> b[i];
  }

  for (int i = 1; i <= m; ++i) {
    int sum = 0, cnt = 0;
    rep(j, n) {
      if (a[j] == i) {
        sum += b[j];
        cnt++;
      }
    }
    printf("%.10f\n", (double)sum/cnt);
  }
}
