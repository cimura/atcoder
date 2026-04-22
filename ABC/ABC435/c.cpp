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
  int max_place = -1;
  rep(i, n) {
    max_place = max(max_place, i + a[i] - 1);
    //cout << "max: " << max_place << endl;
    if (max_place <= i) break;
  }
  cout << min(max_place+1, static_cast<int>(a.size())) << endl;
}
