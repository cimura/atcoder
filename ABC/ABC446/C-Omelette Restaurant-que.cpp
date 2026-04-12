#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

void solve() {
  int n, d; cin >> n >> d;
  vi a(n), b(n);
  rep(j, n) {
    cin >> a[j];
  }
  rep(j, n) {
    cin >> b[j];
  }
  queue<int> stock;
  rep(k, n) {
    rep(l, a[k]) {
      stock.push(k);
    }
    rep(l, b[k]) {
      stock.pop();
    }

    while (!stock.empty() && k - stock.front() >= d) {
      stock.pop();
    }

  }
  cout << stock.size() << endl;
}

int main() {
  int t; cin >> t;
  rep(i, t) solve();
}
