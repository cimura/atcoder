#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

void solve() {
  int n; cin >> n;
  vector<long long> rem_power(n);
  long long max_power = 0;
  rep(i, n) {
    int w, p; cin >> w >> p;
    rem_power[i] = w + p;
    max_power += p;
  }
  sort(rem_power.begin(), rem_power.end());

  int count = 0;
  for (long long elem : rem_power) {
    max_power -= elem;
    if (max_power < 0) {
      cout << count << endl;
      return;
    }
    count++;
  }
}

int main() {
  int t; cin >> t;
  while (t--) {
    solve();
  }
}
