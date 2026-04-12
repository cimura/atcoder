#include <iostream>
#include <iomanip>
#include <cmath>
#include <numbers>

using namespace std;

int main() {
  int n; cin >> n;
  string s; cin >> s;

  int start = 0;
  for (start = 0; start < s.length() && s[start] == 'o'; ++start) {
  }
  if (start == s.length()) cout << "" << endl;
  
  cout << s.substr(start, s.length()) << endl;
}
