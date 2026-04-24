#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1000000000

using ll = long long;

// コンテナかどうかを判定するためのテンプレート（SFINAE）
template <typename T, typename = void>
struct is_container : std::false_type {};

template <typename T>
struct is_container<T, std::void_t<decltype(std::begin(std::declval<T>())), decltype(std::end(std::declval<T>()))>>
  : std::true_type {
};

// 文字列そのものはコンテナ扱いしたくないので除外
template <>
struct is_container<std::string> : std::false_type {};

// デバッグ関数本体
void debug_out() { std::cerr << std::endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T);

template <typename T>
void print_val(const T& x) {
  if constexpr (is_container<T>::value) {
    std::cerr << "{";
    bool first = true;
    for (const auto& i : x) {
      if (!first) std::cerr << ", ";
      print_val(i); // 再帰的に中身を表示
      first = false;
    }
    std::cerr << "}";
  }
  else {
    std::cerr << x;
  }
}

// 複数の引数を受け取れるようにするマクロ用の核
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  print_val(H);
  if (sizeof...(T)) std::cerr << ", ";
  debug_out(T...);
}

// 実行時に変数名も表示するマクロ
#define debug(...) std::cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)

vector<char> s;

void solve() {
  int type;
  char c;

  cin >> type;
  if (!(cin >> c)) {
    c = 0;
  }

  if (type == 1) {
    cout << "c: " << c << endl;
    s.push_back(c);
  }
  else if (s.size()) {
    s.pop_back();
  }
  if (s.size() >= 2) {
    debug_out(s);
    int end_pos = s.size() - 1;
    char c1 = s[end_pos];
    char c2 = s[end_pos - 1];
    if (c1 == '(' && c2 == ')') {
      s.pop_back();
      s.pop_back();
      cout << "Yes\n";
      return;
    } 
  }
  cout << "No\n";
}

int main() {
  int q; cin >> q;
  //cin.ignore();
  rep(i, q) {
    solve();
  }
}
