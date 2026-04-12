#include <bits/stdc++.h>

using namespace std;
#define INF 1000000000

int main() {
  int n, q; cin >> n >> q;
  vector<pair<long long, long long>> a_conntainers(n);
  for (int i = 0; i < n; ++i) {
    int a; cin >> a;
    a_conntainers[i] = { i, a };
  }

  sort(a_conntainers.begin(), a_conntainers.end());

  vector<pair<long long, long long>> top6;
  for (int x = 0; x < 6; ++x) top6.push_back(a_conntainers[x]);

  for (int i = 0; i < q; ++i) {
    int k; cin >> k;
    vector<bool> is_done(6, false);
    for (int j = 0; j < k; ++j) {
      int b; cin >> b;
      for (int l = 0; l < 6; ++l) {
        pair<long long, long long > p = top6[l];
        if (p.second == b) {
          is_done[l] = true;
        }
      }

      for (int l = 0; l < 6; ++l) {
        if (!is_done[l]) {
          cout << top6[l].second << endl;
          break;
        }
      }

    }
  }
}
