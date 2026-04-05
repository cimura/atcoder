#include <bits/stdc++.h>

using namespace std;

int main() {
  int N = 6, R = 10;
  vector<int> X = {1, 7, 15, 20, 30, 50};

  int i = 0;
  while (i < N) {
    int s = X[i++];

    while (i < N && X[i] <= s + R) {
      i++;
    }
    
  }
}
