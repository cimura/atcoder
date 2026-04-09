#include <bits/stdc++.h>

using namespace std;
#define INF 1000000000

int main() {
  int n, q; cin >> n >> q;
  vector<long long> a(n);
  for (int i = 0; i < n; ++i) cin >> a[i];

  vector<int> result;
  for (int i = 0; i < q; ++i) {
    vector<long long> eval = a;
    int k; cin >> k;
    for (int j = 0; j < k; ++j) {
      int b; cin >> b;
      eval[b - 1] = INF;
    }
    cout << *min_element(eval.begin(), eval.end()) << endl;
  }
}
