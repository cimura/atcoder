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
  int len = s.size();

  // ランレングス圧縮
  vector<pair<char, int>> rle;
  for (char c : s) {
    if (rle.size() && rle.back().first == c) rle.back().second++;
    else rle.emplace_back(c, 1);
  }

  int cnt = 0;
  rep(i, rle.size() - 1) {
    if (rle[i + 1].first - rle[i].first != 1) continue;
    cnt += min(rle[i + 1].second, rle[i].second);
  }
  cout << cnt << endl;
}
