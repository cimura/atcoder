#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int main() {
  int n, m; cin >> n >> m;
  string s, t;
  cin >> s;
  cin >> t;
  int q; cin >> q;
  rep(i, q) {
    string w; cin >> w;
    bool s_found, t_found;
    rep(i, static_cast<int>(w.length())) {
      char c = w[i];
      s_found = (find(s.begin(), s.end(), c) == s.end());
      t_found = (find(t.begin(), t.end(), c) == t.end());

      if (!s_found && !t_found) {
        if (static_cast<size_t>(i) == w.length() - 1) {
          cout << "Unknown" << endl;
          break;
        }
        continue;
      }
      else if (!s_found && t_found) {
        cout << "Takahashi" << endl;
        break;
      }
      else if (s_found && !t_found) {
        cout << "Aoki" << endl;
        break;
      }
      else {
        cout << "Unknown" << endl;
        break;
      }
    }
  }
}
