#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int main() {
  int n, k; cin >> n >> k;
  int count = 0;
  rep(i, n + 1) {
    int sum = 0;
    int temp = i;
    while (temp > 0) {
      sum += (temp % 10);
      temp = temp / 10;
    }
    if (sum == k) count++;
  }
  cout << count << endl;
}
