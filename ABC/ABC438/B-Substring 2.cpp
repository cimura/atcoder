#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>

int main() {
  int n, m; cin >> n, m;
  string s, t;
  cin >> s >> t;

  int mm = INT_MAX;
  rep(i, m) {
    string ns = s.substr(i, m);
    string nt = t;
    int cnt = 0;
    int j = 0;
    while (ns[j] != nt[j]) {
      if (nt[j] == '9') nt[j] = '0';
      else nt[j]++;
      j++;
      cnt++;
    }
    mm = min(mm, cnt);
  }
  cout << mm << endl;
}
