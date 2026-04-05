#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

int main() {
  uint32_t Q;
  cin >> Q;

  multiset<uint32_t> niwa;
  for (uint32_t i = 0; i < Q; ++i) {
    uint32_t query, h;
    cin >> query >> h;
    if (query == 1) {
      niwa.insert(h);
    }
    else {
      niwa.erase(niwa.begin(), niwa.lower_bound(h+1));
    }
    cout << niwa.size() << endl;
  }
  return 0;
}
