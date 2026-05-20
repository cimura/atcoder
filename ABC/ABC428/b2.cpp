#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

using ll = long long;

int main() {
  int n, k; string s;
  cin >> n >> k >> s;
  map<string, int> mp;

  rep(i, n - k + 1) {
    string sub = s.substr(i, k);
    //cout << "sub: " << sub << endl;
    mp[sub]++;
  }
  //sort(mp.begin(), mp.end());
  int mx_cnt = 0;
  for (auto cnt : mp) {
    mx_cnt = max(mx_cnt, cnt.second);
  }
  cout << mx_cnt << endl;

  for (auto s : mp) {
    if (mx_cnt == s.second) {
      cout << s.first << " ";
    }
  }
  cout << endl;
}
