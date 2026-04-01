#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  uint32_t n = 0, m = 0;
  cin >> n >> m;

  //cout << "n: " << n << endl;
  vector<uint32_t> a, b;
  for (int i = 0; i < n; ++i) {
    uint32_t A, B;
    cin >> A >> B;
    a.push_back(A);
    //cout << "a -> " << A << endl;
    b.push_back(B);
    //cout << "b -> " << B << endl;
  }

  //cout << "m: " << m << endl;
  for (uint32_t j = 1; j <= m; ++j) {
    auto a_count = count(a.begin(), a.end(), j);
    //cout << "a "<< a_count << endl;
    auto b_count = count(b.begin(), b.end(), j);
    //cout << "b "<< b_count << endl;

    cout << b_count - a_count << endl;
  }
  return 0;
}