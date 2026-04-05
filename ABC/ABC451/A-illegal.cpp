#include <iostream>

using namespace std;

int main() {
  string input;
  cin >> input;

  if (input.size() % 5 == 0) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
}