#include <bits/stdc++.h>

using namespace std;

int main() {
  int N, T; cin >> N >> T;
  int time = 0;
  int open = 0;
  for (int i = 0; i < N; ++i) {
    int A; cin >> A;
    if (open < A) {
      time += (A - open);
      open = A + 100;
    }
  }

  if (open < T) {
    time += T - open;
  }

  cout << time << endl;
}
