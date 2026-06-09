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

int dr[] = { 0, 1, 0, -1 };
int dc[] = { 1, 0, -1, 0 };

// --- 事前計算（キャッシュ）用のグローバル配列 ---
// dist[sr][sc][sdir][tr][tc] = 最短操作回数
int dist_cache[20][20][4][20][20];
// end_dir_memo[sr][sc][sdir][tr][tc] = 到達時の向き
int end_dir_memo[20][20][4][20][20];
// path_memo[sr][sc][sdir][tr][tc] = 操作文字列
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
  // 初期化
  for (int sr = 0; sr < N; ++sr) for (int sc = 0; sc < N; ++sc) for (int sd = 0; sd < 4; ++sd)
    for (int tr = 0; tr < N; ++tr) for (int tc = 0; tc < N; ++tc)
      dist_cache[sr][sc][sd][tr][tc] = INF;

  // すべての (r, c, dir) の状態からBFSを走らせる（1600回）
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

          // 初めて (cr, cc) に到達した時の状態を記録（最短保証）
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

          // F
          if (can_move(cr, cc, cd)) {
            int nr = cr + dr[cd], nc = cc + dc[cd];
            if (get<0>(visited[nr][nc][cd]) == -1) {
              visited[nr][nc][cd] = { cr, cc, cd, 'F' };
              q.push({ nr, nc, cd });
            }
          }
          // R
          int nd_r = (cd + 1) % 4;
          if (get<0>(visited[cr][cc][nd_r]) == -1) {
            visited[cr][cc][nd_r] = { cr, cc, cd, 'R' };
            q.push({ cr, cc, nd_r });
          }
          // L
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

// 評価関数：指定された順番でボールを運んだ時の「基本操作回数（Sも含む）」を計算
int calc_score(const vector<int>& order) {
  int total = 0;
  int r = 0, c = 0, dir = 0;
  for (int i : order) {
    // 現在地 -> ボール
    int tr = balls[i].first, tc = balls[i].second;
    total += dist_cache[r][c][dir][tr][tc] + 1; // +1 は 'S' の分
    dir = end_dir_memo[r][c][dir][tr][tc];
    r = tr; c = tc;

    // ボール -> カゴ
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
  double TIME_LIMIT = 1.85; // 制限時間2.0秒に対し、余裕を持たせる

  // 初期解：とりあえず0番から順に
  vector<int> current_order(M);
  for (int i = 0; i < M; ++i) current_order[i] = i;

  int current_score = calc_score(current_order);
  vector<int> best_order = current_order;
  int best_score = current_score;

  // 温度パラメータ（スコアの変動幅に合わせて調整）
  double T0 = 50.0; // 序盤の温度（悪化を許容しやすい）
  double T1 = 2.0;  // 終盤の温度（悪化を許容しにくい）

  mt19937 mt(42);
  int iter = 0;

  while (true) {
    // 時間確認は重いので一定回数ごとに行う
    if ((iter & 127) == 0) {
      auto now = chrono::high_resolution_clock::now();
      double elapsed = chrono::duration<double>(now - start_time).count();
      if (elapsed > TIME_LIMIT) break;

      // 温度の更新
      double temp = T0 + (T1 - T0) * (elapsed / TIME_LIMIT);

      // 近傍遷移（ランダムな2つのボールの回収順を入れ替える）
      int idx1 = mt() % M;
      int idx2 = mt() % M;
      if (idx1 == idx2) { iter++; continue; }

      swap(current_order[idx1], current_order[idx2]);
      int new_score = calc_score(current_order);

      // 採用判定（スコアが下がる＝良くなるなら確定、悪化しても確率で採用）
      double prob = exp((current_score - new_score) / temp);
      if (new_score <= current_score || (mt() % 10000) / 10000.0 < prob) {
        current_score = new_score;
        if (current_score < best_score) {
          best_score = current_score;
          best_order = current_order;
        }
      }
      else {
        // 不採用なら元に戻す
        swap(current_order[idx1], current_order[idx2]);
      }
    }
    else {
      // 時間計測をスキップするターンも近傍遷移は行う
      int idx1 = mt() % M;
      int idx2 = mt() % M;
      if (idx1 == idx2) { iter++; continue; }
      swap(current_order[idx1], current_order[idx2]);
      int new_score = calc_score(current_order);
      // 簡易的な山登り（温度計算をサボって良くなった時だけ採用）
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

// 動的マクロ更新による強力な圧縮アルゴリズム
string compress_advanced(const string& raw) {
  string res = "";
  int n = raw.size();
  int i = 0;
  string current_macro = "";

  while (i < n) {
    int best_saved = -1;
    string best_cand = "";

    // 1. 現在地(i)から始まる「新しいマクロ」の候補をすべて評価する
    for (int L = 2; L <= 20; ++L) {
      if (i + L > n) break;
      string cand = raw.substr(i, L);
      // 'S' はボールの有無に依存するためマクロ化しない
      if (cand.find('S') != string::npos) continue;

      // 少し先（lookahead）まで見て、この候補が何回出現するか数える
      int lookahead_end = min(n, i + 150); // 150文字先までを評価ウィンドウとする
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

      // 削減文字数の計算: (出現回数 - 1) * (長さ - 1) - 2(MとMの分)
      int saved = (count - 1) * (L - 1) - 2;
      if (saved > best_saved) {
        best_saved = saved;
        best_cand = cand;
      }
    }

    // 2. 「現在記憶しているマクロ」がそのまま使えるか？
    bool can_use_current = false;
    if (!current_macro.empty() && i + current_macro.size() <= n) {
      if (raw.substr(i, current_macro.size()) == current_macro) {
        can_use_current = true;
      }
    }

    // 3. 行動の決定
    // 既存のマクロを使うと (長さ - 1) 文字得する
    int current_savings = can_use_current ? (int)current_macro.size() - 1 : 0;

    // 新しいマクロを定義した方が、既存のマクロを使い続けるより「圧倒的に」得なら上書きする
    if (best_saved > 0 && best_saved > current_savings) {
      res += "M" + best_cand + "M"; // 新規登録
      current_macro = best_cand;
      i += best_cand.size();
    }
    // そうでなくて、既存のマクロが使えるなら使う
    else if (can_use_current) {
      res += "P"; // 再生
      i += current_macro.size();
    }
    // どちらもダメなら1文字そのまま出力
    else {
      res += raw[i];
      i++;
    }
  }
  return res;
}


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  if (!(cin >> N >> M >> T)) return 0;
  v_walls.resize(N); for (int i = 0; i < N; ++i) cin >> v_walls[i];
  h_walls.resize(N - 1); for (int i = 0; i < N - 1; ++i) cin >> h_walls[i];
  balls.resize(M); baskets.resize(M);
  for (int i = 0; i < M; ++i) {
    cin >> balls[i].first >> balls[i].second >> baskets[i].first >> baskets[i].second;
  }

  // 1. キャッシュの構築
  precompute();

  // 2. 焼きなまし法で最適な順番を探す
  vector<int> best_order = solve_sa();

  // 3. 確定した順番から具体的な操作文字列を復元
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

  // 4. マクロで圧縮して出力
  string final_ans = compress(raw_ans);
  int len = min((int)final_ans.size(), T);
  for (int i = 0; i < len; ++i) cout << final_ans[i] << "\n";

  return 0;
}
