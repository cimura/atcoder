#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

using ll = long long;

int main() {
  int n, k; string s; cin >> n >> k >> s;

  map<string, int> cnt;
  rep(i, n-k+1) {
    string sub = s.substr(i, k);
    cnt[sub]++;
  }
  int x = 0;
  for (auto p : cnt) {
    x =  max(x, p.second);
  }
  cout << x << endl;
  for (auto p : cnt) {
    if (x == p.second) {
      cout << p.first << " ";
    }
  }
  cout << endl;
}
