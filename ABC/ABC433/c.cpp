#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

using ll = long long;

int main() {
  string s; cin >> s;
  int len = s.length();

  int cnt = 0;
  for (int i = 0; i < len; i++) {
    for (int j = 0; i - j >= 0 && i + j + 1 < len; ++j) {
      //cout << s[i - j] << ", " << s[i + j + 1] << endl;
      if (abs(s[i - j] - s[i + j + 1]) == 1 && s[i] == s[i - j] &&
        s[i + 1] == s[i + j + 1]) cnt++;
      else break;
    }
  }
  cout << cnt << endl;
}
