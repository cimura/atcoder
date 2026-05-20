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
  int n, l; cin >> n >> l;
  if (l % 3 != 0) {
    cout << 0 << endl;
    return 0;
  }
  vi D(n);
  rep(i, n-1) cin >> D[i+1];

  int top = 0;
  vector<int> v(l);
  v[0]++;
  for (int i = 1; i < n; ++i) {
    int idx = (top + D[i]) % l;
    top = idx;
    v[idx]++;
  }

  //debug_out(v);
  ll ans = 0;
  rep(i, l / 3) {
    int i1 = i;
    int i2 = i + l / 3;
    int i3 = i + l * 2 / 3;

    //cout << i1 << i2 << i3 << endl;
    //cout << "v[i1].size(): " << v[i1].size() << endl;
    //cout << "v[i2].size(): " << v[i2].size() << endl;
    //cout << "v[i3].size(): " << v[i3].size() << endl;
    if (v[i1] && v[i2] && v[i3]) {
      ans += (ll)v[i1] * v[i2] * v[i3];
      //cout << "++ " << ans << endl;
    }
  }
  cout << ans << endl;
  //debug_out(v);
}
