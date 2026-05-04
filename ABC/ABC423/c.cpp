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
  int n, R; cin >> n >> R;
  --R;
  vi L(n);
  rep(i, n) cin >> L[i];
  
  int left = 0, right = n - 1;
  while (l[left] == 1) left++;
  while (l[right] == 1) right--;

  ll ans = 0;
  if (r < left) {
    // r to right
    for (int i = r; i <= right; ++i) {
      if (l[i] == 0) ans++;
      if (l[i] == 1) ans+=2;
    }
  }
  else if (r >= left && r <= right) {
    // left to right
    for (int i = left; i <= right; ++i) {
      if (l[i] == 0) ans++;
      if (l[i] == 1) ans+=2;
    }
  }
  else {
    // left to r
    for (int i = left; i <= r; ++i) {
      if (l[i] == 0) ans++;
      if (l[i] == 1) ans+=2;
    }
  }

  cout << ans << endl;
}
