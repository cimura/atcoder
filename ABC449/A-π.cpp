#include <iostream>
#include <iomanip>
#include <cmath>
#include <numbers>

using namespace std;

int main() {
  int D;
  cin >> D;
  double radius = D/2.0;
  double result = radius * radius * std::numbers::pi;
  cout << fixed << setprecision(13) << result << endl;
  //printf("%e\n", result);
}
