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

  sort(a.begin(), a.end());
  int result = 0;
  result += a.size() - k;
  int drunk = 0;
  rep(i, n) {
    if (drunk > x) break;
    drunk += a[i];
    result++;
  }
  cout << result << endl;
}
