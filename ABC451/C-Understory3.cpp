#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>

using namespace std;

int main() {
  int Q;
  cin >> Q;

  priority_queue<int, vector<int>, greater<int>> niwa;
  for (int i = 0; i < Q; ++i) {
    int query, h;
    cin >> query >> h;
    if (query == 1) {
      niwa.push(h);
    }
    else {
      while (!niwa.empty() and niwa.top() <= h) {
        niwa.pop();
      }
    }
    cout << niwa.size() << endl;
  }
  return 0;
}
