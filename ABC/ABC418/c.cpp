#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
#define vll vector<long long>
#define vs vector<string>
#define INF 1010001000

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

int min3(int a, int b, int c) {
  int m = a;
  if (m > b) m = b;
  if (m > c) m = c;
  return m;
}

int max3(int a, int b, int c) {
  int m = a;
  if (m < b) m = b;
  if (m < c) m = c;
  return m;
}

// 実行時に変数名も表示するマクロ
#define debug(...) std::cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)

int main() {
  int n, q; cin >> n >> q;
  vi a(n);
  ll sum = 0;
  vll r_sum(n + 1);
  rep(i, n) {
    cin >> a[i];
  }
  sort(a.begin(), a.end());

  rep(i, n) {
    sum += a[i];
    r_sum[i + 1] = r_sum[i] + a[i];
  }
  //debug_out(a);
  while (q--) {
    int b; cin >> b;
    auto pos = upper_bound(a.begin(), a.end(), b - 1);
    int dis = distance(a.begin(), pos);
    ll ans = r_sum[dis];
    ans += (ll)(b - 1) * (n - dis);
    //cout << "b-1: " << b - 1 << ", pos: " << dis << endl;
    if (sum == ans) cout << -1 << endl;
    else cout << ans + 1 << endl;
  }

}
