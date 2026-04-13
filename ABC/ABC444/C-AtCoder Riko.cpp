#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int main() {
  int n; cin >> n;
  vi a(n);
  rep(i,n) cin >> a[i];

  sort(a.begin(), a.end());

  /**
   * 1. 割れてない l = max
   * 2. 割れてる l = min + max
   */
  rep(i, n) {
    
  }
}
