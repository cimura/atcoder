#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int main() {
  int t; cin >> t;
  rep(i, t) {
    int n, d; cin >> n >> d;
    vi a(n), b(n);
    rep(j, n) {
      cin >> a[j];
    }
    rep(j, n) {
      cin >> b[j];
    }
    vector<int> stock;
    rep(k, n) {
      rep(l, a[k]) {
        stock.push_back(l);
      }
      rep(l, b[k]) {
        stock.erase(stock.begin());
      }

      rep(o, stock.size()) {
        if (k - stock[o] >= d) {
          stock.erase(stock.begin() + o);
        }
      }
    }
    cout << stock.size() << endl;
  }
}
