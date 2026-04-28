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
  auto func = [&](int num) {
    if (num == 0) return 1;
    string s = to_string(num);
    int ans = 0;

    for (int i = s.size() - 1; i >= 0; --i) {
      ans += s[i] - '0';
    }
    return ans;
  };
  
  vi a(n+1);
  int ans = 0;
  a[0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < i; ++j) {
      a[i] += func(a[j]);
    }
  }
  cout << a[n] << endl;
}
