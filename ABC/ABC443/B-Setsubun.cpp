#include <bits/stdc++.h>

using namespace std;

int main() {
  int N, K; cin >> N >> K;
  int count = 0;

  int total = N;
  int prev = N+1;
  while (total < K) {
    total += prev;
    //if (total > K) break;
    count++;
    prev += 1;
  }
  cout << count << endl;
}

