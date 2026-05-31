#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<double>
#define vs vector<string>
#define INF 1000000000

int main() {
  int n; cin >> n;
  vs vec(n);
  rep(i, n) cin >> vec[i];
  for (string s : vec) {
    char c = s[0];
    int cnt = 0;
    if (c == 'a' || c == 'b' || c == 'c') cnt = 2;
    if (c == 'd' || c == 'e' || c == 'f') cnt = 3;
    if (c == 'g' || c == 'h' || c == 'i') cnt = 4;
    if (c == 'j' || c == 'k' || c == 'l') cnt = 5;
    if (c == 'm' || c == 'n' || c == 'o') cnt = 6;
    if (c == 'p' || c == 'q' || c == 'r' || c == 's') cnt = 7;
    if (c == 't' || c == 'u' || c == 'v') cnt = 8;
    if (c == 'w' || c == 'x' || c == 'y' || c == 'z') cnt = 9;
    cout << cnt;
  }
  cout << endl;
}

