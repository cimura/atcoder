#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

using ll = long long;

int main() {
  string x; cin >> x;
  sort(x.begin(), x.end());

  int z = 0;
  while (x[z] == '0') {
    z++;
  }
  swap(x[0], x[z]);
  rep(i, x.length()) {
    cout << x[i];
  }
  cout << endl;
}
