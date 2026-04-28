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
  for (char c : s) {
    if (count(s.begin(), s.end(), c) == 1) {
      cout << c << endl;
    }
  }
}
