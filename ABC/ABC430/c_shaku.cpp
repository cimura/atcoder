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
  int n, a, b; cin >> n >> a >> b;
  string s; cin >> s;
  vi A(n + 1), B(n + 1);
  rep(i, n) {
    A[i + 1] = A[i] + (s[i] == 'a');
    B[i + 1] = B[i] + (s[i] == 'b');
  }

  //debug_out(A);
  //debug_out(B);

  // 累積和+尺取り法
  int ans = 0;
  for (int l = 1; l <= n; ++l) {
    // r_1: 'a' が a 個以上になる最小のインデックス
    int r1 = 1;
    int r2 = 1;
    while (r1 <= n) {
      if (A[r1] - A[l-1] >= a) break;
      r1++;
    }
    // r_2: 'b' が b 個以上になる最小のインデックス
    if (r2 < r1) r2 = r1;
    while (r2 <= n) {
      if (B[r2] - B[l-1] >= b) break;
      r2++;
    }
    ans += r2 - r1;
  }
  cout << ans << endl;
}
