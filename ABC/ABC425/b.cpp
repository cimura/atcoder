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
  set<int> st;
  for (int i = 1; i <= n; ++i) st.insert(i);
  rep(i, n) {
    cin >> a[i];
  }

  rep(i, n) {
    if (a[i] != -1) {
      st.erase(a[i]);
    }
  }

  rep(i, n) {
    if (a[i] == -1) {
      a[i] = *st.begin();
      st.erase(st.begin());
    }
  }
  if (st.size() > 0) {
    cout << "No\n";
    return 0;
  }
  cout << "Yes\n";
  rep(i, n) {
    cout << a[i] << " ";
  }
  cout << endl;
}
