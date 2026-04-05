#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

int main() {
  multiset<uint32_t> niwa{1, 2, 3, 4, 5};
  //auto end = niwa.lower_bound(3);
  niwa.erase(niwa.begin(), niwa.lower_bound(3));
  cout << niwa.size() << endl;
  //for (auto it=niwa.begin(); it != end; ++it) cout << *it << endl;
  return 0;
}
