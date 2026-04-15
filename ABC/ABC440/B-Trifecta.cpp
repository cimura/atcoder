#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int main() {
  int n; cin >> n;
  vector<pair<int, int> > a(n);
  rep(i,n) {
    int t; cin >> t;
    a[i] = {t, i};
  }
  sort(a.begin(), a.end());
  cout << a[0].second+1 << " ";
  cout << a[1].second+1 << " ";
  cout << a[2].second+1 << " ";
}
