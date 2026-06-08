#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <map>
#include <algorithm>

using namespace std;

const int INF = 1e9;
int N, M, T;
vector<string> v_walls, h_walls;
vector<pair<int, int>> balls, baskets;

// 0=右, 1=下, 2=左, 3=上
int dr[] = { 0, 1, 0, -1 };
int dc[] = { 1, 0, -1, 0 };

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

// BFSで最短経路を求める
pair<string, int> bfs(int sr, int sc, int sdir, int tr, int tc) {
  queue<tuple<int, int, int>> q;
  q.push({ sr, sc, sdir });

  vector<vector<vector<tuple<int, int, int, char>>>> visited(
    N, vector<vector<tuple<int, int, int, char>>>(N, vector<tuple<int, int, int, char>>(4, { -1, -1, -1, ' ' })));

  visited[sr][sc][sdir] = { -2, -2, -2, ' ' };

  while (!q.empty()) {
    auto [cr, cc, cd] = q.front();
    q.pop();

    if (cr == tr && cc == tc) {
      string path = "";
      int curr_r = cr, curr_c = cc, curr_d = cd;
      while (true) {
        auto [pr, pc, pd, act] = visited[curr_r][curr_c][curr_d];
        if (pr == -2) break;
        path += act;
        curr_r = pr; curr_c = pc; curr_d = pd;
      }
      reverse(path.begin(), path.end());
      return { path, cd };
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
  return { "", sdir };
}

// マクロ圧縮（1パターン）
string compress(const string& raw) {
  int best_len = 0;
  string best_sub = "";
  int max_saved = 0;

  for (int len = 2; len <= 15; ++len) {
    map<string, int> counts;
    for (int i = 0; i <= (int)raw.size() - len; ++i) {
      string sub = raw.substr(i, len);
      if (sub.find('S') != string::npos) continue;
      counts[sub]++;
    }

    for (auto& kv : counts) {
      int occurrences = kv.second;
      int saved = (occurrences - 1) * (len - 1) - 2;
      if (saved > max_saved) {
        max_saved = saved;
        best_sub = kv.first;
        best_len = len;
      }
    }
  }

  if (max_saved <= 0) return raw;

  string res = "";
  bool first = true;
  for (int i = 0; i < (int)raw.size(); ) {
    if (i <= (int)raw.size() - best_len && raw.substr(i, best_len) == best_sub) {
      if (first) {
        res += "M" + best_sub + "M";
        first = false;
      }
      else {
        res += "P";
      }
      i += best_len;
    }
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

  v_walls.resize(N);
  for (int i = 0; i < N; ++i) cin >> v_walls[i];

  h_walls.resize(N - 1);
  for (int i = 0; i < N - 1; ++i) cin >> h_walls[i];

  balls.resize(M);
  baskets.resize(M);
  for (int i = 0; i < M; ++i) {
    cin >> balls[i].first >> balls[i].second;
    cin >> baskets[i].first >> baskets[i].second;
  }

  // --- ここから貪欲法（Greedy）に書き換え ---
  int curr_r = 0, curr_c = 0, curr_dir = 0;
  string raw_ans = "";

  // ボールiを運んだかどうかを管理
  vector<bool> visited(M, false);

  for (int step = 0; step < M; ++step) {
    int best_ball_idx = -1;
    int min_dist = INF;
    string best_path_to_ball = "";
    int best_dir_at_ball = 0;

    // 1. 最も近い未回収のボールを探す
    for (int i = 0; i < M; ++i) {
      if (visited[i]) continue;

      auto [path, dir_at_ball] = bfs(curr_r, curr_c, curr_dir, balls[i].first, balls[i].second);
      int dist = path.size();

      if (dist < min_dist) {
        min_dist = dist;
        best_ball_idx = i;
        best_path_to_ball = path;
        best_dir_at_ball = dir_at_ball;
      }
    }

    // 2. そのボールを取りに行く
    raw_ans += best_path_to_ball + "S";

    // 3. 対応するカゴに置きに行く
    auto [path_to_basket, end_dir_k] = bfs(
      balls[best_ball_idx].first, balls[best_ball_idx].second, best_dir_at_ball,
      baskets[best_ball_idx].first, baskets[best_ball_idx].second
    );
    raw_ans += path_to_basket + "S";

    // 4. ロボットの状態と訪問フラグを更新
    curr_r = baskets[best_ball_idx].first;
    curr_c = baskets[best_ball_idx].second;
    curr_dir = end_dir_k;
    visited[best_ball_idx] = true;
  }
  // --- ここまで ---

  string final_ans = compress(raw_ans);

  int len = min((int)final_ans.size(), T);
  for (int i = 0; i < len; ++i) {
    cout << final_ans[i] << "\n";
  }

  return 0;
}
