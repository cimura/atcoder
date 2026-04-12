#include <bits/stdc++.h>

using namespace std;

int main() {
  string s; cin >> s;

  int max_count = -1;

  vector<pair<int, char>> count_pairs;
  for (int i = 0; i < s.length(); ++i) {
    int n = count(s.begin(), s.end(), s[i]);
    if (max_count <= n) {
      count_pairs.push_back({ n, s[i] });
      max_count = n;
      //max_c = s[i];
    }
  }


  vector<char> skips;
  for (auto cp: count_pairs) {
    if (max_count == cp.first) {
      skips.push_back(cp.second);
    }
  }

  //for (auto a: skips) cout << a << endl;

  for (auto c : s) {
    if (find(skips.begin(), skips.end(), c) != skips.end()) continue;
    cout << c;
  }
  cout << endl;
}
