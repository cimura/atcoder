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

int min3(int a, int b, int c) {
  int m = a;
  if (m > b) m = b;
  if (m > c) m = c;
  return m;
}

int main() {
  int H, W; cin >> H >> W;
  vs vec(H);
  rep(i, H) cin >> vec[i];

  // bfs
  vector<vector<bool>> seen(H, vector<bool>(W, false));
  int dx[4] = { 1, -1, 0, 0 };
  int dy[4] = { 0, 0, 1, -1 };

  auto dfs = [&](auto dfs, int h, int w) -> void {
    seen[h][w] = true;
    for (int i = 0; i < 4; ++i) {
      int nh = h + dy[i];
      int nw = w + dx[i];
      if (nh < 0 || nh >= H || nw < 0 || nw >= W)continue;
      if (seen[nh][nw]) continue;
      if (vec[nh][nw] == '#') continue;
      dfs(dfs, nh, nw);
    }
    };

  int start_x = 0, start_y = 0;
  int goal_x = 0, goal_y = 0;
  rep(i, H) rep(j, W) {
    if (vec[i][j] == 's') {
      start_x = i;
      start_y = j;
    }
    else if (vec[i][j] == 'g') {
      goal_x = i;
      goal_y = j;
    }
  }
  dfs(dfs, start_x, start_y);
  if (seen[goal_x][goal_y]) {
    cout << "Yes" << endl;
  }
  else {
    cout << "No" << endl;
  }
}
