#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int main() {
  string s; int n;
  cin >> s >> n;
  for (int i = n; i < s.length() - n;++i) {
    cout << s[i];
  }
  cout << endl;
}
