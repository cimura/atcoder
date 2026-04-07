#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <numbers>

using namespace std;

bool is_contain(string src, string target) {
  int ti = 0;
  for (int i = 0; i < src.size(); ++i) {
    if (src[i] == target[ti]) {
      ti++;
    }
  }
  if (ti == target.size()) return true;
  return false;
}

int main() {
  string S, T;
  cin >> S >> T;
  int len = S.length();
  int count = 0;

  for (int bit = 0; bit < (1 << len); ++bit) {
    string s = "";
    for (int i = 0; i < len; ++i) {
      if (bit & (1 << i)) {
        s += S[i];
      }
    }
    //cout << s << endl;
    if (!s.empty() && !is_contain(s, T)) count++;
  }
  cout << count << endl;
}
