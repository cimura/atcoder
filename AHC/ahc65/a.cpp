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

int N;
vector<vector<int>> board; // マス(r, c)にある箱番号
vector<pair<int, int>> pos;           // 箱番号kの現在の座標(r, c)

struct Move {
  int m, d;
};

vector<Move> history;
vector<vector<vector<int>>> cell_to_conv;

// d:
// 0 = 上
// 1 = 下
// 2 = 左
// 3 = 右
void move_conveyor(int m, int d) {
  history.push_back({ m, d });
  if (m < N) {
    int r = m;
    if (d == 2) {
      int x = board[r][0];
      for (int c = 0; c < N - 1; ++c) {
        board[r][c] = board[r][c + 1];
      }
      board[r][N - 1] = x;
    }
    else if (d == 3) {
      int x = board[r][N - 1];
      for (int c = N - 1; c >= 1; --c) {
        board[r][c] = board[r][c - 1];
      }
      board[r][0] = x;
    }

    rep(c, N) {
      int k = board[r][c];
      if (k != -1) {
        pos[k] = { r, c };
      }
    }
  }

  else {
    int c = m - N;
    if (d == 0) {
      int x = board[0][c];
      for (int r = 0; r < N - 1; ++r) {
        board[r][c] = board[r + 1][c];
      }
      board[N - 1][c] = x;
    }
    else if (d == 1) {
      int x = board[N - 1][c];
      for (int r = N - 1; r >= 1; --r) {
        board[r][c] = board[r - 1][c];
      }
      board[0][c] = x;
    }

    rep(r, N) {
      int k = board[r][c];
      if (k != -1) {
        pos[k] = { r, c };
      }
    }
  }

  // ここで実際にboardとposを更新する処理が必要
  // 簡略化のため、ここでは「移動した」というシミュレーションを行うこと
}

int main() {
  cin >> N;
  pos.assign(N * N, { -1, -1 });
  board.assign(N, vector<int>(N));
  rep(i, N) rep(j, N) {
    cin >> board[i][j];
    pos[board[i][j]] = { i, j };
  }

  cell_to_conv.resize(N, vector<vector<int>>(N));
  cout << 2 * N << endl;
  rep(i, N) {
    cout << N;
    rep(j, N) {
      cout << " " << i << " " << j;
      cell_to_conv[i][j].push_back(i);
    }
    cout << endl;
  }
  rep(j, N) {
    cout << N;
    rep(i, N) {
      cout << " " << i << " " << j;
      cell_to_conv[i][j].push_back(N + j);
    }
    cout << endl;
  }

  int goal_r = 0;
  int goal_c = N / 2;

  for (int target = 0; target < N * N; target++) {
    if (pos[target].first == -1) continue;

    int r = pos[target].first;
    int c = pos[target].second;

    while (c != goal_c) {
      int right_dist = (goal_c - c + N) % N;
      int left_dist = (c - goal_c + N) % N;

      if (right_dist <= left_dist) {
        move_conveyor(r, 3);
      }
      else {
        move_conveyor(r, 2);
      }

      r = pos[target].first;
      c = pos[target].second;
    }

    while (r != goal_r) {
      int up_dist = (r - goal_r + N) % N;
      int down_dist = (goal_r - r + N) % N;

      if (up_dist <= down_dist) {
        move_conveyor(N + c, 0);
      }
      else {
        move_conveyor(N + c, 1);
      }

      r = pos[target].first;
      c = pos[target].second;
    }

    board[goal_r][goal_c] = -1;
    pos[target] = { -1, -1 };
  }
}
