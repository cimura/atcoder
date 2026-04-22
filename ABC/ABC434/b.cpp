#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

using ll = long long;

int main() {
  int n, m; cin >> n >> m;
  vector<pair<int, double>> bird(m+1);
  rep(i, n) {
    int a, b; cin >> a >> b;
    bird.push_back({i, b});
  }

  rep(i, n) {
    cout << find(bird
    )
  }
}
