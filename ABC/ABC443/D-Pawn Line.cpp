#include <bits/stdc++.h>

using namespace std;

// ソートされたvector
int calc_diff(vector<int> v) {
  auto it = v.begin(); 
  int result = 0;
  while (it != v.end()) {
    //cout << "D: " << *it << endl;
    auto next = it + 1;
    if (abs(*next - *it) > 1) {
      if (*next - *it > 0) *it += 1;
      else *next += 1;
      it = v.begin();
      result++;
    }
    it++;
  }
  return result;
}

int main() {
  int T; cin >> T;
  for (int i = 0; i < T; ++i) {
    int N; cin >> N;
    vector<int> v(N);
    for (int j = 0; j < N; ++j) {
      int r; cin >> v[j];
    }
    //sort(v.begin(), v.end());
    cout << calc_diff(v) << endl;
  }
}
