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



int main() {
  int a; string n; cin >> a >> n;
  // judge pali
  auto f = [&](ll num) {
    string s = "";
    while (num > 0) {
      s += (num % a) + '0';
      num /= a;
    }
    string s_rev = s;
    reverse(s_rev.begin(), s_rev.end());
    return s == s_rev;
    };
  // convert nth
  ll num = stoll(n);
  ll ans = 0;
  for (int i = 1; i <= 1e6; ++i) {
    string left = to_string(i);
    string right = left;
    reverse(right.begin(), right.end());

    string s1 = left + right.substr(1);
    ll val1 = stoll(s1);
    if (val1 <= num && f(val1)) {
      ans += val1;
    }
    string s2 = left + right;
    ll val2 = stoll(s2);
    if (val2 <= num && f(val2)) {
      ans += val2;
    }
  }
  cout << ans << endl;
}
