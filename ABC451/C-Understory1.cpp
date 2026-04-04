#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  uint32_t Q;
  cin >> Q;

  vector<uint32_t> niwa;
  for (uint32_t i = 0; i < Q; ++i) {
    uint32_t query, h;
    cin >> query >> h;
    if (query == 1) {
      niwa.push_back(h);
    }
    else {
        erase_if(niwa, [h](uint32_t n) { return n <= h;});
    }
    cout << niwa.size() << endl;
  }
  return 0;
}
