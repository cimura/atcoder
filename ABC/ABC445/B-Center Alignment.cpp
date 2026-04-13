#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int main() {
  int n; cin >> n;
  long unsigned int max_len = 0;
  vs ss(n);
  rep(i, n) {
    string s; cin >> s;
    ss[i] = s;
    max_len = max(s.length(), max_len);
  }

  rep(i, n) {
    string s = ss[i];
    //cout << "s: " << s << endl;
    int len = s.length();
    int dot_count = (max_len - len) / 2;
    //cout << "dot count: " << dot_count << endl;
    rep(j, dot_count) s.insert(s.begin(), '.');
    rep(k, dot_count) s.push_back('.');
    cout << s << endl;
  }
}
