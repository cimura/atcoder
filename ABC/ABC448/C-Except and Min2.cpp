#include <bits/stdc++.h>

using namespace std;
#define INF 1000000000

int main() {
  int n, q; cin >> n >> q;
  // pairで保持
  vector<pair<int, int>> balls(n);
  for (int i = 0; i < n; ++i) {
    int a; cin >> a;
    balls[i] = { a, i + 1 };
  }

  sort(balls.begin(), balls.end());
  // top6
  vector<pair<int, int>>top6;
  for (int j = 0; j < min(n, 6); ++j) {
    top6.push_back(balls[j]);
  }

  vector<int> result;
  for (int i = 0; i < q; ++i) {
    int k; cin >> k;
    set<int> removed;
    for (int j = 0; j < k; ++j) {
      int b; cin >> b;
      removed.insert(b);
    }

    for (auto t : top6) {
      if (removed.find(t.second) == removed.end()) {
        cout << t.first << endl;
        break;
      }
    }
  }
}
