#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int main() {
  string s; cin >> s;
  string ans = "";
  for (char c : s) {
    if (c >= '0' && c <= '9') {
      ans += c;
    }
  }
  cout << ans;
  if (ans.size()) cout << endl;
}
