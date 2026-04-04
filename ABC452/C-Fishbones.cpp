#include <iostream>
#include <iomanip>
#include <cmath>
#include <numbers>

using namespace std;



int main() {
  int N;
  cin >> N;

  vector<pair<int, int>> v;
  for (int i = 0; i < N; ++i) {
    int A, B;
    cin >> A >> B;

    v.push_back({ A, B });
  }

  int M;
  cin >> M;
  vector<string> s_vect;
  for (int i = 0; i < M; ++i) {
    string word;
    cin >> word;
    s_vect.push_back(word);
  }

  //for (int i = 0; i < v.size(); ++i) {
  for (int j = 0; j < s_vect.size(); ++j) {
    string word = s_vect[j];
    for (int k = 0; k < word.size(); ++k) {
      for (int a = 0; a < v.size(); ++a) {
        pair<int, int> p = v[a];
        if ()p.first
      }
    }
  }
  //}
}
