#include <bits/stdc++.h>

using namespace std;

/**
 * まずは判定を考える
 * 次に手数を考える
 *
 *
 * ex) AABCA
 *     ABAC
 * 各文字の区切りに注目して、それぞれの差分の絶対値の和を求める
 */

string removeA(string s) {
  string res = "";
  for (char c : s) {
    if (c == 'A');
    else res += c;
  }
  return res;
}

vector<int> f(std::string s) {
  vector<int> res = { 0 };
  for (char c : s) {
    if (c == 'A') res.back()++;
    else res.push_back(0);
  }
  return res;
}

int main() {
  string s, t; cin >> s >> t;

  if (removeA(s) != removeA(t)) cout << -1 << endl;
  else {
    int ans = 0;
    auto sa = f(s);
    auto ta = f(t);
    for (int i = 0; i < sa.size(); ++i) {
      ans += abs(sa[i] - ta[i]);
    }
    cout << ans << endl;
  }
}
