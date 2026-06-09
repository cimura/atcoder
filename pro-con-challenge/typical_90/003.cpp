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

using G = vector<vector<int>>;

int main() {
  auto dfs = [&](const G& graph, int start) -> pair<int, int> {
    int N = graph.size();
    stack<int> st;
    vector<int> dist(N, -1);
    dist[start] = 0;
    st.push(start);
    while (st.size()) {
      int v = st.top();
      st.pop();
      for (auto u : graph[v]) {
        if (dist[u] != -1) continue;
        dist[u] = dist[v] + 1;
        st.push(u);
      }
    }
    int farthest = start;
    rep(i, N) {
      if (dist[i] > dist[farthest]) {
        farthest = i;
      }
    }
    return { farthest, dist[farthest] };
    };

  int n; cin >> n;

  G graph(n);
  rep(i, n - 1) {
    int a, b;
    cin >> a >> b;
    --a; --b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }
  auto [u, _] = dfs(graph, 0);
  auto [v, diameter] = dfs(graph, u);
  cout << diameter + 1 << endl;
}
