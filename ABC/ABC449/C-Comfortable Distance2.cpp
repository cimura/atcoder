#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int main() {
  int n, l, r; cin >> n >> l >> r;
  string s; cin >> s;

  map<int, int> mp;
  rep(i, s.length()) {
    mp[s[i] - 'a']++;
  }

  int count = 0;
  rep(j, n) {
  }
  cout << count << endl;
}
