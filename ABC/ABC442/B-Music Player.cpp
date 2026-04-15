#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

int main() {
  int q; cin >> q;
  int volume = 0;
  int stop = true;
  rep(i, q) {
    int a; cin >> a;
    if (a == 1) {
      volume++;
    }
    else if (a == 2) {
      if (volume >= 1) volume--;
      else if (volume == 0) {

      }
    }
    else if (a == 3) {
      stop = !stop;
    }
    if (volume >= 3 && !stop) {
      cout << "Yes"  << endl;
    }
    else {
      cout << "No"  << endl;
    }
  }
}
