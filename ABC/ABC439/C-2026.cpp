#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int main() {
  int n; cin >> n;
  vi result;
  for (int z = 1; z <= n; ++z) {
    int count = 0;
    for (int x = 1; x < n / 2; ++x) {
      for (int y = x + 1; y < n / 2; ++y) {
        if (x * x + y * y == z) {
          //cout << "x: " << x << ", y: " << y << ", z: " << z << endl;
          count++;
        }
      }
    }
    if (count == 1) {
      //cout << z << " ";
      result.push_back(z);
    }
  }
  cout << result.size() << endl;
  for (auto r: result) cout << r << " ";
  cout << endl;
}
