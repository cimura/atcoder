#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <map>
#include <algorithm>

using namespace std;

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

  // visited[r][c][dir] = {prev_r, prev_c, prev_dir, action}
  vector<vector<vector<tuple<int, int, int, char>>>> visited(
    N, vector<vector<tuple<int, int, int, char>>>(N, vector<tuple<int, int, int, char>>(4, { -1, -1, -1, ' ' })));

  visited[sr][sc][sdir] = { -2, -2, -2, ' ' }; // スタートの印

  while (!q.empty()) {
    auto [cr, cc, cd] = q.front();
    q.pop();

    if (cr == tr && cc == tc) {
      string path = "";
      int curr_r = cr, curr_c = cc, curr_d = cd;
      while (true) {
        auto [pr, pc, pd, act] = visited[curr_r][curr_c][curr_d];
        if (pr == -2) break; // スタート地点
        path += act;
        curr_r = pr; curr_c = pc; curr_d = pd;
      }
      reverse(path.begin(), path.end());
      return { path, cd };
    }

    // F (前進)
    if (can_move(cr, cc, cd)) {
      int nr = cr + dr[cd], nc = cc + dc[cd];
      if (get<0>(visited[nr][nc][cd]) == -1) {
        visited[nr][nc][cd] = { cr, cc, cd, 'F' };
        q.push({ nr, nc, cd });
      }
    }

    // R (右折)
    int nd_r = (cd + 1) % 4;
    if (get<0>(visited[cr][cc][nd_r]) == -1) {
      visited[cr][cc][nd_r] = { cr, cc, cd, 'R' };
      q.push({ cr, cc, nd_r });
    }

    // L (左折)
    int nd_l = (cd + 3) % 4;
    if (get<0>(visited[cr][cc][nd_l]) == -1) {
      visited[cr][cc][nd_l] = { cr, cc, cd, 'L' };
      q.push({ cr, cc, nd_l });
    }
  }
  return { "", sdir };
}

// 文字列の中から最も効果的なパターンを見つけてマクロ圧縮する
string compress(const string& raw) {
  int best_len = 0;
  string best_sub = "";
  int max_saved = 0;

  // 長さ2〜15の部分文字列を探索
  for (int len = 2; len <= 15; ++len) {
    map<string, int> counts;
    for (int i = 0; i <= (int)raw.size() - len; ++i) {
      string sub = raw.substr(i, len);
      // 'S'を含むマクロは状態（ボールの有無）に依存するため最初は避ける
      if (sub.find('S') != string::npos) continue;
      counts[sub]++;
    }

    // 最も「文字数が削減できる」パターンを探す
    for (auto& kv : counts) {
      int occurrences = kv.second;
      // 削減文字数 = (置換回数 - 1) * (文字列長 - 1) - 2(Mの登録分)
      int saved = (occurrences - 1) * (len - 1) - 2;
      if (saved > max_saved) {
        max_saved = saved;
        best_sub = kv.first;
        best_len = len;
      }
    }
  }

  if (max_saved <= 0) return raw; // 圧縮効果がない場合はそのまま返す

  // 圧縮を実行
  string res = "";
  bool first = true;
  for (int i = 0; i < (int)raw.size(); ) {
    if (i <= (int)raw.size() - best_len && raw.substr(i, best_len) == best_sub) {
      if (first) {
        res += "M" + best_sub + "M"; // 初回はマクロ登録
        first = false;
      }
      else {
        res += "P"; // 2回目以降は再生
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

  // 1. ナイーブに F, R, L, S だけの文字列を構築
  int curr_r = 0, curr_c = 0, curr_dir = 0;
  string raw_ans = "";

  for (int i = 0; i < M; ++i) {
    auto [path_b, end_dir_b] = bfs(curr_r, curr_c, curr_dir, balls[i].first, balls[i].second);
    raw_ans += path_b + "S";
    curr_r = balls[i].first; curr_c = balls[i].second; curr_dir = end_dir_b;

    auto [path_k, end_dir_k] = bfs(curr_r, curr_c, curr_dir, baskets[i].first, baskets[i].second);
    raw_ans += path_k + "S";
    curr_r = baskets[i].first; curr_c = baskets[i].second; curr_dir = end_dir_k;
  }

  // 2. マクロ圧縮（ランレングス的な置換）
  string final_ans = compress(raw_ans);

  // T回を超えないように出力
  int len = min((int)final_ans.size(), T);
  for (int i = 0; i < len; ++i) {
    cout << final_ans[i] << "\n";
  }

  return 0;
}
