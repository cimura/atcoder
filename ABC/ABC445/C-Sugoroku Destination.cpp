#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

#define BOUND 10

int solve(vector<int> a, int idx) {
  for (int i = 0; i < BOUND; ++i) {
    int next = a[idx]-1;
    idx = next;
  }
  return idx+1;
}

int main() {
  int n; cin >> n;
  vector<int> a(n + 1);
  rep(i, n) cin >> a[i];

  rep(i, n) {
    if (i != 0) cout << " ";
    cout << solve(a, i);
  }
  cout << endl;
}
