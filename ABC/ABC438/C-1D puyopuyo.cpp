#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

bool is_bingo(vector<int> q) {
  if (q.size() < 4) return false;
  int a, b, c, d;
  a = q.back(); q.pop_back();
  b = q.back(); q.pop_back();
  c = q.back(); q.pop_back();
  d = q.back(); q.pop_back();
  //cout << "a " << a << " b " << b << " c " << c << " d " << d << endl;
  if (a == b && b == c && c == d) {
    return true;
  }
  return false;
}

int main() {
  int n; cin >> n;
  vector<int> q;

  int cnt = 0;
  rep(i, n) {
    int a; cin >> a;
    q.push_back(a);
    if (is_bingo(q)) {
      rep(j, 4) if (!q.empty()) q.pop_back();
    }
  }
  cout << q.size() << endl;
}
