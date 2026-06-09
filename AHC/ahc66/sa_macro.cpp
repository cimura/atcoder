#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <map>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <random>

using namespace std;

const int INF = 1e9;
int N, M, T;
vector<string> v_walls, h_walls;
vector<pair<int, int>> balls, baskets;

// 0=右, 1=下, 2=左, 3=上
int dr[] = { 0, 1, 0, -1 };
int dc[] = { 1, 0, -1, 0 };

// --- 事前計算（キャッシュ）用のグローバル配列 ---
int dist_cache[20][20][4][20][20];
int end_dir_memo[20][20][4][20][20];
string path_memo[20][20][4][20][20];

bool can_move(int r, int c, int d) {
  int nr = r + dr[d];
  int nc = c + dc[d];
  if (nr < 0 || nr >= N || nc < 0 || nc >= N) return false;
  if (d == 0) return v_walls[r][c] == '0';
  if (d == 1) return h_walls[r][c] == '0';
  if (d == 2) return v_walls[r][c - 1] == '0';
  if (d == 3) return h_walls[r - 1][c] == '0';
  return false;
}

// 1. 全点対最短経路の事前計算（BFS）
void precompute() {
  for (int sr = 0; sr < N; ++sr) for (int sc = 0; sc < N; ++sc) for (int sd = 0; sd < 4; ++sd)
    for (int tr = 0; tr < N; ++tr) for (int tc = 0; tc < N; ++tc)
      dist_cache[sr][sc][sd][tr][tc] = INF;

  for (int sr = 0; sr < N; ++sr) {
    for (int sc = 0; sc < N; ++sc) {
      for (int sdir = 0; sdir < 4; ++sdir) {
        queue<tuple<int, int, int>> q;
        vector<vector<vector<tuple<int, int, int, char>>>> visited(
          N, vector<vector<tuple<int, int, int, char>>>(N, vector<tuple<int, int, int, char>>(4, { -1, -1, -1, ' ' })));

        q.push({ sr, sc, sdir });
        visited[sr][sc][sdir] = { -2, -2, -2, ' ' };
        dist_cache[sr][sc][sdir][sr][sc] = 0;
        end_dir_memo[sr][sc][sdir][sr][sc] = sdir;
        path_memo[sr][sc][sdir][sr][sc] = "";

        while (!q.empty()) {
          auto [cr, cc, cd] = q.front();
          q.pop();

          if (dist_cache[sr][sc][sdir][cr][cc] == INF) {
            string path = "";
            int curr_r = cr, curr_c = cc, curr_d = cd;
            while (true) {
              auto [pr, pc, pd, act] = visited[curr_r][curr_c][curr_d];
              if (pr == -2) break;
              path += act;
              curr_r = pr; curr_c = pc; curr_d = pd;
            }
            reverse(path.begin(), path.end());
            dist_cache[sr][sc][sdir][cr][cc] = path.size();
            end_dir_memo[sr][sc][sdir][cr][cc] = cd;
            path_memo[sr][sc][sdir][cr][cc] = path;
          }

          if (can_move(cr, cc, cd)) {
            int nr = cr + dr[cd], nc = cc + dc[cd];
            if (get<0>(visited[nr][nc][cd]) == -1) {
              visited[nr][nc][cd] = { cr, cc, cd, 'F' };
              q.push({ nr, nc, cd });
            }
          }
          int nd_r = (cd + 1) % 4;
          if (get<0>(visited[cr][cc][nd_r]) == -1) {
            visited[cr][cc][nd_r] = { cr, cc, cd, 'R' };
            q.push({ cr, cc, nd_r });
          }
          int nd_l = (cd + 3) % 4;
          if (get<0>(visited[cr][cc][nd_l]) == -1) {
            visited[cr][cc][nd_l] = { cr, cc, cd, 'L' };
            q.push({ cr, cc, nd_l });
          }
        }
      }
    }
  }
}

// 評価関数：指定された順番の合計操作回数（Sを含む）
int calc_score(const vector<int>& order) {
  int total = 0;
  int r = 0, c = 0, dir = 0;
  for (int i : order) {
    int tr = balls[i].first, tc = balls[i].second;
    total += dist_cache[r][c][dir][tr][tc] + 1;
    dir = end_dir_memo[r][c][dir][tr][tc];
    r = tr; c = tc;

    tr = baskets[i].first; tc = baskets[i].second;
    total += dist_cache[r][c][dir][tr][tc] + 1;
    dir = end_dir_memo[r][c][dir][tr][tc];
    r = tr; c = tc;
  }
  return total;
}

// 2. 焼きなまし法（Simulated Annealing）
vector<int> solve_sa() {
  auto start_time = chrono::high_resolution_clock::now();
  double TIME_LIMIT = 1.85; // 2.0秒制限に対するマージン

  vector<int> current_order(M);
  for (int i = 0; i < M; ++i) current_order[i] = i;

  int current_score = calc_score(current_order);
  vector<int> best_order = current_order;
  int best_score = current_score;

  double T0 = 50.0;
  double T1 = 2.0;
  mt19937 mt(42);
  int iter = 0;

  while (true) {
    if ((iter & 127) == 0) {
      auto now = chrono::high_resolution_clock::now();
      double elapsed = chrono::duration<double>(now - start_time).count();
      if (elapsed > TIME_LIMIT) break;

      double temp = T0 + (T1 - T0) * (elapsed / TIME_LIMIT);

      int idx1 = mt() % M;
      int idx2 = mt() % M;
      if (idx1 == idx2) { iter++; continue; }

      swap(current_order[idx1], current_order[idx2]);
      int new_score = calc_score(current_order);

      double prob = exp((current_score - new_score) / temp);
      if (new_score <= current_score || (mt() % 10000) / 10000.0 < prob) {
        current_score = new_score;
        if (current_score < best_score) {
          best_score = current_score;
          best_order = current_order;
        }
      }
      else {
        swap(current_order[idx1], current_order[idx2]);
      }
    }
    else {
      int idx1 = mt() % M;
      int idx2 = mt() % M;
      if (idx1 == idx2) { iter++; continue; }
      swap(current_order[idx1], current_order[idx2]);
      int new_score = calc_score(current_order);
      if (new_score <= current_score) {
        current_score = new_score;
        if (current_score < best_score) {
          best_score = current_score;
          best_order = current_order;
        }
      }
      else {
        swap(current_order[idx1], current_order[idx2]);
      }
    }
    iter++;
  }
  return best_order;
}

// 3. 閾値付きの動的マクロ圧縮
string compress_advanced(const string& raw) {
  string res = "";
  int n = raw.size();
  int i = 0;
  string current_macro = "";

  while (i < n) {
    int best_saved = -1;
    string best_cand = "";

    for (int L = 2; L <= 20; ++L) {
      if (i + L > n) break;
      string cand = raw.substr(i, L);
      if (cand.find('S') != string::npos) continue;

      int lookahead_end = min(n, i + 150);
      int count = 0;
      int j = i;
      while (j <= lookahead_end - L) {
        if (raw.substr(j, L) == cand) {
          count++;
          j += L;
        }
        else {
          j++;
        }
      }

      int saved = (count - 1) * (L - 1) - 2;
      if (saved > best_saved) {
        best_saved = saved;
        best_cand = cand;
      }
    }

    bool can_use_current = false;
    if (!current_macro.empty() && i + current_macro.size() <= n) {
      if (raw.substr(i, current_macro.size()) == current_macro) {
        can_use_current = true;
      }
    }

    int current_savings = can_use_current ? (int)current_macro.size() - 1 : 0;

    // ★ マクロの「浮気防止」閾値（+4）
    if (best_saved > 0 && best_saved > current_savings + 4) {
      res += "M" + best_cand + "M";
      current_macro = best_cand;
      i += best_cand.size();
    }
    else if (can_use_current) {
      res += "P";
      i += current_macro.size();
    }
    else {
      res += raw[i];
      i++;
    }
  }
  return res;
}

int main() {
  // 入出力の高速化
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  if (!(cin >> N >> M >> T)) return 0;

  v_walls.resize(N);
  for (int i = 0; i < N; ++i) cin >> v_walls[i];

  h_walls.resize(N - 1);
  for (int i = 0; i < N - 1; ++i) cin >> h_walls[i];

  balls.resize(M); baskets.resize(M);
  for (int i = 0; i < M; ++i) {
    cin >> balls[i].first >> balls[i].second >> baskets[i].first >> baskets[i].second;
  }

  // 1. キャッシュの構築
  precompute();

  // 2. 焼きなまし法で最適な順番を探索
  vector<int> best_order = solve_sa();

  // 3. 確定した順番から基本操作列を復元
  string raw_ans = "";
  int r = 0, c = 0, dir = 0;
  for (int i : best_order) {
    int tr = balls[i].first, tc = balls[i].second;
    raw_ans += path_memo[r][c][dir][tr][tc] + "S";
    dir = end_dir_memo[r][c][dir][tr][tc];
    r = tr; c = tc;

    tr = baskets[i].first; tc = baskets[i].second;
    raw_ans += path_memo[r][c][dir][tr][tc] + "S";
    dir = end_dir_memo[r][c][dir][tr][tc];
    r = tr; c = tc;
  }

  // 4. 動的マクロ圧縮を実行
  string final_ans = compress_advanced(raw_ans);

  // T回の制限を超えないように出力
  int len = min((int)final_ans.size(), T);
  for (int i = 0; i < len; ++i) {
    cout << final_ans[i] << "\n";
  }

  return 0;
}
