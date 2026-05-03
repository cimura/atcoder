#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<double>
#define vs vector<string>
#define INF 1000000000

int main() {
  int n = 6;
  vi a1(n), a2(n), a3(n);

  double ans = 0;
  rep(i, n) cin >> a1[i];
  rep(i, n) cin >> a2[i];
  rep(i, n) cin >> a3[i];
  // a1 = 4, a2 = 5, a3 = 6
  {
    double a1_e = (double)count(a1.begin(), a1.end(), 4) / 6;
    double a2_e = (double)count(a2.begin(), a2.end(), 5) / 6;
    double a3_e = (double)count(a3.begin(), a3.end(), 6) / 6;
    ans += a1_e * a2_e * a3_e;
  }
  // a1 = 4, a2 = 6, a3 = 5
  {
    double a1_e = (double)count(a1.begin(), a1.end(), 4) / 6;
    double a2_e = (double)count(a2.begin(), a2.end(), 6) / 6;
    double a3_e = (double)count(a3.begin(), a3.end(), 5) / 6;
    ans += a1_e * a2_e * a3_e;
  }

  // a1 = 5, a2 = 4, a3 = 6
  {
    double a1_e = (double)count(a1.begin(), a1.end(), 5) / 6;
    double a2_e = (double)count(a2.begin(), a2.end(), 4) / 6;
    double a3_e = (double)count(a3.begin(), a3.end(), 6) / 6;
    ans += a1_e * a2_e * a3_e;
  }
  // a1 = 5, a2 = 6, a3 = 4
  {
    double a1_e = (double)count(a1.begin(), a1.end(), 5) / 6;
    double a2_e = (double)count(a2.begin(), a2.end(), 6) / 6;
    double a3_e = (double)count(a3.begin(), a3.end(), 4) / 6;
    ans += a1_e * a2_e * a3_e;
  }

  // a1 = 6, a2 = 4, a3 = 5
  {
    double a1_e = (double)count(a1.begin(), a1.end(), 6) / 6;
    double a2_e = (double)count(a2.begin(), a2.end(), 4) / 6;
    double a3_e = (double)count(a3.begin(), a3.end(), 5) / 6;
    ans += a1_e * a2_e * a3_e;
  }
  // a1 = 6, a2 = 5, a3 = 4
  {
    double a1_e = (double)count(a1.begin(), a1.end(), 6) / 6;
    double a2_e = (double)count(a2.begin(), a2.end(), 5) / 6;
    double a3_e = (double)count(a3.begin(), a3.end(), 4) / 6;
    ans += a1_e * a2_e * a3_e;
  }
  cout << std::fixed << setprecision(10) << ans << endl;
}

