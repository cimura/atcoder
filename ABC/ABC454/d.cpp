#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

bool found(stack<char> s) {
  if (s.size() < 4) return false;
  string str = "";
  rep(i, 4) {
    str.push_back(s.top());
    s.pop();
  }
  return str == "(xx)";
}

void solve() {
  string a, b; cin >> a >> b;
  if (a == b) {
    cout << "Yes" << endl;
    return;
  }

  stack<char> sa;
  for (char c : a) {
    sa.push(c);
    if (found(sa)) {
      rep(i, 4) if (!sa.empty()) sa.pop();
    }
  }

  for (char c: sa) cout << c << " ";
  cout << endl << endl;

  stack<char> sb;
  for (char c : b) {
    sb.push(c);
    if (found(sb)) {
      rep(i, 4) if (!sb.empty()) sb.pop();
    }
  }
  for (char c: sa) cout << c << " ";
  cout << endl;

  if (sa == sb) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
}

int main() {
  int t; cin >> t;
  while (--t) {
    solve();
  }
}
