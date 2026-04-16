#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int main() {
  int n; cin >> n;
  vi v;

  long long h = n;
  while (1) {
    long long temp = 0;
    while (n > 0) {
      temp += (n % 10) * (n % 10);
      n /= 10;
    }
    //cout << "h: " << h << endl;
    h = temp;
    n = temp;
    if (find(v.begin(), v.end(), h) != v.end()) {
      break;
    }
    if (h == 1) {
      cout << "Yes" << endl;
      return 0;
    }
    v.push_back(h);
  }
  cout << "No" << endl;
}
