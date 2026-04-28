#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

using ll = long long;

int main() {
  int n, m, k; cin >> n >> m >> k;
  vector<int> scores(n);
  rep(i, k) {
    int a, b; cin >> a >> b;
    --a; --b;
    scores[a]++;
    if (scores[a] >= m) {
      cout << a+1 << " ";
    }
  }
  cout << endl;
  
}
