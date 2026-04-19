#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int main() {
  auto sum = [&](int a, int b) {
    return a + b;
  };

  cout << sum(3, 4) << endl;
  cout << sum(8, 4) << endl;
  cout << sum(3, 12) << endl;
}
