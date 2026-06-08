#include <bits/stdc++.h>
using namespace std;

namespace {
  using Clock = chrono::steady_clock;
  constexpr int INF = 1e9;

  int N, M, T;
  vector<string> vwall, hwall;
  vector<pair<int, int>> balls, baskets, points;
  int state_count, source_count;
  vector<vector<int>> dist_from;
  vector<vector<short>> parent_from;
  vector<vector<char>> action_from;
  const int DR[4] = { 0,1,0,-1 };
  const int DC[4] = { 1,0,-1,0 };

  int sid(int r, int c, int d) { return ((r * N + c) << 2) | d; }
  void decode(int s, int& r, int& c, int& d) { d = s & 3; int p = s >> 2; r = p / N; c = p % N; }
  int srcid(int p, int d) { return (p << 2) | d; }

  bool can_move(int r, int c, int d) {
    int nr = r + DR[d], nc = c + DC[d];
    if (nr < 0 || nr >= N || nc < 0 || nc >= N) return false;
    if (d == 0) return vwall[r][c] == '0';
    if (d == 1) return hwall[r][c] == '0';
    if (d == 2) return vwall[r][c - 1] == '0';
    return hwall[r - 1][c] == '0';
  }

  void precompute() {
    state_count = N * N * 4;
    source_count = (int)points.size() * 4;
    dist_from.assign(source_count, vector<int>(state_count, INF));
    parent_from.assign(source_count, vector<short>(state_count, -1));
    action_from.assign(source_count, vector<char>(state_count, '?'));
    vector<int> q(state_count);
    for (int p = 0;p < (int)points.size();++p) {
      auto [sr, sc] = points[p];
      for (int sd = 0;sd < 4;++sd) {
        int source = srcid(p, sd), st = sid(sr, sc, sd);
        int head = 0, tail = 0; q[tail++] = st;
        dist_from[source][st] = 0;
        parent_from[source][st] = (short)st;
        auto push = [&](int from, int to, char a) {
          if (dist_from[source][to] != INF) return;
          dist_from[source][to] = dist_from[source][from] + 1;
          parent_from[source][to] = (short)from;
          action_from[source][to] = a;
          q[tail++] = to;
          };
        while (head < tail) {
          int cur = q[head++], r, c, d; decode(cur, r, c, d);
          if (can_move(r, c, d)) push(cur, sid(r + DR[d], c + DC[d], d), 'F');
          push(cur, sid(r, c, (d + 1) & 3), 'R');
          push(cur, sid(r, c, (d + 3) & 3), 'L');
        }
      }
    }
  }

  int trans_cost(int fp, int fd, int tp, int td) {
    auto [r, c] = points[tp];
    return dist_from[srcid(fp, fd)][sid(r, c, td)];
  }

  array<int, 4> advance_dp(const array<int, 4>& dp, int fp, int tp) {
    array<int, 4> ndp; ndp.fill(INF);
    for (int fd = 0;fd < 4;++fd) if (dp[fd] < INF) {
      for (int td = 0;td < 4;++td) {
        int d = trans_cost(fp, fd, tp, td);
        if (d < INF) ndp[td] = min(ndp[td], dp[fd] + d + 1); // +S
      }
    }
    return ndp;
  }

  int route_cost(const vector<int>& order) {
    array<int, 4> dp = { 0,INF,INF,INF };
    int cur = 0;
    for (int item : order) {
      int bp = 1 + 2 * item, kp = 2 + 2 * item;
      dp = advance_dp(dp, cur, bp); cur = bp;
      dp = advance_dp(dp, cur, kp); cur = kp;
    }
    return *min_element(dp.begin(), dp.end());
  }

  vector<int> greedy_order(mt19937& rng, int width) {
    vector<int> ord; ord.reserve(M);
    vector<char> used(M, 0);
    array<int, 4> dp = { 0,INF,INF,INF };
    int cur = 0;
    for (int step = 0;step < M;++step) {
      struct C { int score, item, endp; array<int, 4> dp; };
      vector<C> cs;
      for (int i = 0;i < M;++i) if (!used[i]) {
        int bp = 1 + 2 * i, kp = 2 + 2 * i;
        auto a = advance_dp(dp, cur, bp);
        auto b = advance_dp(a, bp, kp);
        cs.push_back({ *min_element(b.begin(),b.end()),i,kp,b });
      }
      sort(cs.begin(), cs.end(), [](const C& a, const C& b) {return a.score < b.score;});
      int w = min(width, (int)cs.size());
      int pick = (w == 1 ? 0 : (int)(rng() % w));
      auto c = cs[pick];
      used[c.item] = 1; ord.push_back(c.item); dp = c.dp; cur = c.endp;
    }
    return ord;
  }

  struct RouteCand { int cost; vector<int> order; };
  void keep_route(vector<RouteCand>& out, const vector<int>& ord, int cost) {
    for (auto& x : out) if (x.order == ord) return;
    out.push_back({ cost,ord });
    sort(out.begin(), out.end(), [](auto& a, auto& b) {return a.cost < b.cost;});
    if (out.size() > 16) out.resize(16);
  }

  vector<RouteCand> optimize_routes(const Clock::time_point& start) {
    mt19937 rng(42);
    vector<RouteCand> pool;
    vector<int> id(M); iota(id.begin(), id.end(), 0);
    keep_route(pool, id, route_cost(id));
    for (int w : {1, 2, 2, 3, 3, 4, 4}) { auto g = greedy_order(rng, w); keep_route(pool, g, route_cost(g)); }
    vector<int> cur = pool.front().order; int curc = pool.front().cost;
    int best = curc; vector<int> bestord = cur;
    uniform_real_distribution<double> U(0.0, 1.0);
    const double deadline = 0.45;
    double t0 = max(4.0, best * 0.02), t1 = 0.15;
    long long it = 0;
    while (true) {
      if ((it & 255) == 0) {
        double e = chrono::duration<double>(Clock::now() - start).count();
        if (e >= deadline) break;
      }
      double e = chrono::duration<double>(Clock::now() - start).count();
      double prog = min(1.0, e / deadline);
      double temp = t0 * pow(t1 / t0, prog);
      vector<int> nxt = cur;
      int a = rng() % M, b = rng() % M; if (a == b) { ++it;continue; } if (a > b) swap(a, b);
      int op = rng() % 10;
      if (op < 4) swap(nxt[a], nxt[b]);
      else if (op < 7) reverse(nxt.begin() + a, nxt.begin() + b + 1);
      else { int x = nxt[a]; nxt.erase(nxt.begin() + a); nxt.insert(nxt.begin() + b, x); }
      int nc = route_cost(nxt), diff = nc - curc;
      if (diff <= 0 || U(rng) < exp(-(double)diff / temp)) {
        cur = move(nxt); curc = nc;
        if (curc < best) { best = curc;bestord = cur;keep_route(pool, bestord, best); }
        else if ((it & 4095) == 0 && curc <= best + 10) keep_route(pool, cur, curc);
      }
      if ((it & 32767) == 32767 && pool.size() > 1 && prog < 0.9) {
        int k = rng() % min<size_t>(pool.size(), 6); cur = pool[k].order; curc = pool[k].cost;
      }
      ++it;
    }
    keep_route(pool, bestord, best);
    return pool;
  }

  string restore_segment(int fp, int fd, int tp, int td) {
    int source = srcid(fp, fd); auto [tr, tc] = points[tp];
    int cur = sid(tr, tc, td); auto [sr, sc] = points[fp]; int st = sid(sr, sc, fd);
    string rev;
    while (cur != st) {
      int par = parent_from[source][cur];
      if (par < 0) return {};
      rev.push_back(action_from[source][cur]);
      cur = par;
    }
    reverse(rev.begin(), rev.end()); return rev;
  }

  string build_raw(const vector<int>& order) {
    vector<int> target; target.reserve(2 * M);
    for (int x : order) { target.push_back(1 + 2 * x);target.push_back(2 + 2 * x); }
    vector<array<int, 4>> pre(target.size());
    array<int, 4> dp = { 0,INF,INF,INF }; int curp = 0;
    for (int s = 0;s < (int)target.size();++s) {
      array<int, 4> ndp; ndp.fill(INF); pre[s].fill(-1);
      for (int fd = 0;fd < 4;++fd) if (dp[fd] < INF) {
        for (int td = 0;td < 4;++td) {
          int val = dp[fd] + trans_cost(curp, fd, target[s], td) + 1;
          if (val < ndp[td]) { ndp[td] = val; pre[s][td] = fd; }
        }
      }
      dp = ndp; curp = target[s];
    }
    int d = min_element(dp.begin(), dp.end()) - dp.begin();
    vector<int> endd(target.size());
    for (int s = (int)target.size() - 1;s >= 0;--s) { endd[s] = d; d = pre[s][d]; }
    string raw; raw.reserve(*min_element(dp.begin(), dp.end()));
    curp = 0; d = 0;
    for (int s = 0;s < (int)target.size();++s) {
      raw += restore_segment(curp, d, target[s], endd[s]); raw.push_back('S');
      curp = target[s]; d = endd[s];
    }
    return raw;
  }

  struct RH {
    static constexpr uint64_t B = 1000003ULL;
    vector<uint64_t> pw, pre;
    RH(const string& s) { pw.resize(s.size() + 1);pre.resize(s.size() + 1);pw[0] = 1;for (size_t i = 0;i < s.size();++i) { pw[i + 1] = pw[i] * B;pre[i + 1] = pre[i] * B + (unsigned char)s[i] + 1; } }
    uint64_t get(int l, int r)const { return pre[r] - pre[l] * pw[r - l]; }
  };

  struct Macro { string body; int len; int gain; uint64_t hash; };

  vector<Macro> make_macros(const string& raw) {
    const int L = raw.size();
    RH rh(raw);
    struct Tmp { int gain, len, pos, count; };
    vector<Tmp> cand;
    const int MAXLEN = min(96, L);
    for (int len = 2;len <= MAXLEN;++len) {
      unordered_map<uint64_t, pair<int, int>> mp;
      mp.reserve(max(16, L - len + 1));
      for (int i = 0;i + len <= L;++i) {
        auto h = rh.get(i, i + len);
        auto it = mp.find(h);
        if (it == mp.end()) mp.emplace(h, make_pair(1, i));
        else ++it->second.first;
      }
      for (auto& kv : mp) {
        int cnt = kv.second.first, pos = kv.second.second;
        if (cnt < 2) continue;
        int gain = (cnt - 1) * (len - 1) - 2;
        if (gain > 0) cand.push_back({ gain,len,pos,cnt });
      }
    }
    sort(cand.begin(), cand.end(), [](const Tmp& a, const Tmp& b) {if (a.gain != b.gain)return a.gain > b.gain;return a.len > b.len;});
    vector<Macro> out; out.reserve(220);
    unordered_set<string> seen;
    for (auto& x : cand) {
      string s = raw.substr(x.pos, x.len);
      if (seen.insert(s).second) { out.push_back({ s,x.len,x.gain,rh.get(x.pos,x.pos + x.len) }); if (out.size() >= 220) break; }
    }
    return out;
  }

  string encode_body(const string& raw, int pos, int len, const string* old) {
    string out; int end = pos + len;
    for (int i = pos;i < end;) {
      if (old && !old->empty() && i + (int)old->size() <= end && raw.compare(i, old->size(), *old) == 0) { out.push_back('P'); i += old->size(); }
      else { out.push_back(raw[i]); ++i; }
    }
    return out;
  }

  struct BNode { int pos, macro, cost, parent; string emit; };

  string beam_compress(const string& raw, const Clock::time_point& start) {
    int L = raw.size();
    if (L == 0) return {};
    auto macros = make_macros(raw);
    int K = macros.size(), EMPTY = K;
    RH rh(raw);
    vector<vector<int>> starts(L);
    for (int m = 0;m < K;++m) {
      int len = macros[m].len;
      for (int i = 0;i + len <= L;++i) {
        if (rh.get(i, i + len) == macros[m].hash) starts[i].push_back(m);
      }
    }
    for (auto& v : starts) {
      sort(v.begin(), v.end(), [&](int a, int b) {return macros[a].gain > macros[b].gain;});
      if (v.size() > 14) v.resize(14);
    }
    const int BW = 110;
    vector<vector<int>> best(L + 1, vector<int>(K + 1, -1));
    vector<BNode> nodes; nodes.reserve((L + 1) * 20);
    auto add = [&](int pos, int macro, int cost, int par, string emit) {
      if (pos > L) return;
      int& slot = best[pos][macro];
      if (slot == -1 || cost < nodes[slot].cost) {
        slot = nodes.size(); nodes.push_back({ pos,macro,cost,par,move(emit) });
      }
      };
    add(0, EMPTY, 0, -1, "");
    for (int pos = 0;pos < L;++pos) {
      if (chrono::duration<double>(Clock::now() - start).count() > 1.72) break;
      vector<int> ids;
      for (int m = 0;m <= K;++m) if (best[pos][m] != -1) ids.push_back(best[pos][m]);
      sort(ids.begin(), ids.end(), [&](int a, int b) {return nodes[a].cost < nodes[b].cost;});
      if (ids.size() > BW) ids.resize(BW);
      for (int id : ids) {
        auto st = nodes[id];
        add(pos + 1, st.macro, st.cost + 1, id, string(1, raw[pos]));
        if (st.macro != EMPTY) {
          auto& mb = macros[st.macro].body;
          if (pos + (int)mb.size() <= L && rh.get(pos, pos + (int)mb.size()) == macros[st.macro].hash)
            add(pos + mb.size(), st.macro, st.cost + 1, id, "P");
        }
        for (int nm : starts[pos]) {
          if (nm == st.macro) continue;
          const string* old = (st.macro == EMPTY ? nullptr : &macros[st.macro].body);
          string body = encode_body(raw, pos, macros[nm].len, old);
          string emit = "M" + body + "M";
          add(pos + macros[nm].len, nm, st.cost + (int)emit.size(), id, move(emit));
        }
      }
    }
    int bestid = -1;
    for (int m = 0;m <= K;++m) { int id = best[L][m]; if (id != -1 && (bestid == -1 || nodes[id].cost < nodes[bestid].cost)) bestid = id; }
    if (bestid == -1) return raw;
    vector<string> parts;
    for (int id = bestid;id != -1;id = nodes[id].parent) parts.push_back(nodes[id].emit);
    reverse(parts.begin(), parts.end());
    string out; for (auto& s : parts) out += s;
    if (out.size() >= raw.size()) return raw;
    return out;
  }



  int apply_basic_state(int state, char op) {
    int r, c, d; decode(state, r, c, d);
    if (op == 'F') {
      if (can_move(r, c, d)) { r += DR[d]; c += DC[d]; }
    }
    else if (op == 'R') d = (d + 1) & 3;
    else if (op == 'L') d = (d + 3) & 3;
    return sid(r, c, d);
  }

  int apply_macro_state(int state, const string& macro) {
    for (char ch : macro) state = apply_basic_state(state, ch);
    return state;
  }

  vector<string> make_navigation_macros(const string& raw) {
    unordered_map<string, int> count;
    count.reserve(raw.size() * 8 + 64);
    const int L = raw.size();
    for (int i = 0;i < L;++i) {
      if (raw[i] == 'S') continue;
      string cur;
      for (int len = 1;len <= 28 && i + len <= L;++len) {
        char ch = raw[i + len - 1];
        if (ch == 'S') break;
        cur.push_back(ch);
        if (len >= 2) ++count[cur];
      }
    }
    for (int len = 2;len <= 16;++len) {
      count[string(len, 'F')] += 2;
      count["R" + string(len, 'F')] += 1;
      count["L" + string(len, 'F')] += 1;
      count[string(len, 'F') + "R"] += 1;
      count[string(len, 'F') + "L"] += 1;
    }
    struct C { int score; string s; };
    vector<C> cs;
    for (auto& kv : count) {
      const string& x = kv.first;
      int cnt = kv.second;
      if (cnt < 2 || x.size() < 2) continue;
      int score = (cnt - 1) * ((int)x.size() - 1) - ((int)x.size() + 2);
      if (score > 0 || (x.size() >= 3 && cnt >= 3)) cs.push_back({ score,x });
    }
    sort(cs.begin(), cs.end(), [](const C& a, const C& b) {
      if (a.score != b.score) return a.score > b.score;
      return a.s.size() > b.s.size();
      });
    vector<string> out;
    unordered_set<string> seen;
    for (auto& c : cs) {
      if (seen.insert(c.s).second) {
        out.push_back(c.s);
        if (out.size() >= 26) break;
      }
    }
    return out;
  }

  struct MacroPlanner {
    string macro;
    vector<int> pnext;
    vector<vector<int>> dist;
    vector<vector<short>> parent;
    vector<vector<char>> action;
    int activated_state = 0;

    explicit MacroPlanner(string m) :macro(move(m)) {
      pnext.resize(state_count);
      for (int s = 0;s < state_count;++s) pnext[s] = apply_macro_state(s, macro);
      activated_state = pnext[sid(0, 0, 0)];
      int sources = 1 + (int)points.size() * 4;
      dist.assign(sources, vector<int>(state_count, INF));
      parent.assign(sources, vector<short>(state_count, -1));
      action.assign(sources, vector<char>(state_count, '?'));
      vector<int> q(state_count);
      for (int source = 0;source < sources;++source) {
        int start_state;
        if (source == 0) start_state = activated_state;
        else {
          int z = source - 1, p = z / 4, d = z % 4;
          auto [r, c] = points[p]; start_state = sid(r, c, d);
        }
        int head = 0, tail = 0; q[tail++] = start_state;
        dist[source][start_state] = 0;
        parent[source][start_state] = (short)start_state;
        auto push = [&](int from, int to, char op) {
          if (dist[source][to] != INF) return;
          dist[source][to] = dist[source][from] + 1;
          parent[source][to] = (short)from;
          action[source][to] = op;
          q[tail++] = to;
          };
        while (head < tail) {
          int cur = q[head++];
          push(cur, pnext[cur], 'P');
          push(cur, apply_basic_state(cur, 'F'), 'F');
          push(cur, apply_basic_state(cur, 'R'), 'R');
          push(cur, apply_basic_state(cur, 'L'), 'L');
        }
      }
    }

    int source_for_point(int p, int d)const { return 1 + p * 4 + d; }

    array<int, 4> advance(const array<int, 4>& dp, int from_point, int to_point)const {
      array<int, 4> ndp; ndp.fill(INF);
      auto [tr, tc] = points[to_point];
      if (from_point == -1) {
        for (int td = 0;td < 4;++td) ndp[td] = dist[0][sid(tr, tc, td)] + 1;
        return ndp;
      }
      for (int fd = 0;fd < 4;++fd) if (dp[fd] < INF) {
        int source = source_for_point(from_point, fd);
        for (int td = 0;td < 4;++td) {
          int d = dist[source][sid(tr, tc, td)];
          if (d < INF) ndp[td] = min(ndp[td], dp[fd] + d + 1);
        }
      }
      return ndp;
    }

    int route_cost(const vector<int>& order)const {
      array<int, 4> dp = { 0,INF,INF,INF };
      int cur = -1;
      for (int item : order) {
        int bp = 1 + 2 * item, kp = 2 + 2 * item;
        dp = advance(dp, cur, bp); cur = bp;
        dp = advance(dp, cur, kp); cur = kp;
      }
      return *min_element(dp.begin(), dp.end()) + (int)macro.size() + 2;
    }

    vector<int> greedy(mt19937& rng, int width)const {
      vector<int> ord; ord.reserve(M); vector<char> used(M, 0);
      array<int, 4> dp = { 0,INF,INF,INF }; int cur = -1;
      for (int step = 0;step < M;++step) {
        struct C { int score, item, endp;array<int, 4> dp; }; vector<C> cs;
        for (int i = 0;i < M;++i) if (!used[i]) {
          int bp = 1 + 2 * i, kp = 2 + 2 * i; auto a = advance(dp, cur, bp); auto b = advance(a, bp, kp);
          cs.push_back({ *min_element(b.begin(),b.end()),i,kp,b });
        }
        sort(cs.begin(), cs.end(), [](const C& a, const C& b) {return a.score < b.score;});
        int w = min(width, (int)cs.size()), pick = w == 1 ? 0 : (int)(rng() % w); auto c = cs[pick];
        used[c.item] = 1;ord.push_back(c.item);dp = c.dp;cur = c.endp;
      }
      return ord;
    }

    string restore(int source, int target_state)const {
      string rev; int cur = target_state;
      while (parent[source][cur] != cur) {
        if (parent[source][cur] < 0) return {};
        rev.push_back(action[source][cur]); cur = parent[source][cur];
      }
      reverse(rev.begin(), rev.end()); return rev;
    }

    string build_controller(const vector<int>& order)const {
      vector<int> targets;targets.reserve(2 * M);
      for (int x : order) { targets.push_back(1 + 2 * x);targets.push_back(2 + 2 * x); }
      vector<array<int, 4>> pre(targets.size());
      array<int, 4> dp = { 0,INF,INF,INF }; int curp = -1;
      for (int i = 0;i < (int)targets.size();++i) {
        array<int, 4> ndp;ndp.fill(INF);pre[i].fill(-1);auto [tr, tc] = points[targets[i]];
        if (curp == -1) {
          for (int td = 0;td < 4;++td) { ndp[td] = dist[0][sid(tr, tc, td)] + 1;pre[i][td] = -2; }
        }
        else {
          for (int fd = 0;fd < 4;++fd) if (dp[fd] < INF) {
            int source = source_for_point(curp, fd);
            for (int td = 0;td < 4;++td) { int val = dp[fd] + dist[source][sid(tr, tc, td)] + 1;if (val < ndp[td]) { ndp[td] = val;pre[i][td] = fd; } }
          }
        }
        dp = ndp;curp = targets[i];
      }
      int d = min_element(dp.begin(), dp.end()) - dp.begin();vector<int>endd(targets.size());
      for (int i = (int)targets.size() - 1;i >= 0;--i) { endd[i] = d;if (i > 0)d = pre[i][d]; }
      string out = "M" + macro + "M";curp = -1;d = 0;
      for (int i = 0;i < (int)targets.size();++i) {
        auto [tr, tc] = points[targets[i]];int target_state = sid(tr, tc, endd[i]);
        int source = (curp == -1 ? 0 : source_for_point(curp, d));
        out += restore(source, target_state);out.push_back('S');curp = targets[i];d = endd[i];
      }
      return out;
    }
  };

  pair<string, vector<int>> try_navigation_macros(const string& baseline_raw, const vector<RouteCand>& routes, const Clock::time_point& start) {
    string best;vector<int> best_order;
    auto macros = make_navigation_macros(baseline_raw);
    mt19937 rng(1234567);
    for (const string& macro : macros) {
      if (chrono::duration<double>(Clock::now() - start).count() > 1.70) break;
      MacroPlanner planner(macro);
      vector<int> cur;int curc = INF;
      for (auto& r : routes) { int c = planner.route_cost(r.order);if (c < curc) { curc = c;cur = r.order; } }
      for (int w : {1, 2, 3}) { auto g = planner.greedy(rng, w);int c = planner.route_cost(g);if (c < curc) { curc = c;cur = move(g); } }
      for (int it = 0;it < 900;++it) {
        vector<int> nxt = cur;int a = rng() % M, b = rng() % M;if (a == b)continue;if (a > b)swap(a, b);int op = rng() % 3;
        if (op == 0)swap(nxt[a], nxt[b]);else if (op == 1)reverse(nxt.begin() + a, nxt.begin() + b + 1);else { int x = nxt[a];nxt.erase(nxt.begin() + a);nxt.insert(nxt.begin() + b, x); }int c = planner.route_cost(nxt);if (c <= curc) { curc = c;cur = move(nxt); }
      }
      string controller = planner.build_controller(cur);
      if (best.empty() || controller.size() < best.size()) { best = move(controller);best_order = move(cur); }
    }
    return { best,best_order };
  }

  bool expand_controller(const string& ctrl, string& expanded) {
    expanded.clear(); string reg, rec; bool recording = false;
    for (char ch : ctrl) {
      if (ch == 'F' || ch == 'R' || ch == 'L' || ch == 'S') {
        expanded.push_back(ch); if (recording) rec.push_back(ch);
      }
      else if (ch == 'M') {
        if (!recording) { recording = true;rec.clear(); }
        else { recording = false;reg = rec; }
      }
      else if (ch == 'P') {
        expanded += reg; if (recording) rec += reg;
      }
      else return false;
      if ((int)expanded.size() > T) return false;
    }
    return !recording;
  }

  bool raw_ok(const string& raw) {
    if ((int)raw.size() > T) return false;
    vector<vector<int>> cell(N, vector<int>(N, -1));
    for (int i = 0;i < M;++i) cell[balls[i].first][balls[i].second] = i;
    int r = 0, c = 0, d = 0, hand = -1;
    for (char ch : raw) {
      if (ch == 'F') { if (can_move(r, c, d)) { r += DR[d];c += DC[d]; } }
      else if (ch == 'R') d = (d + 1) & 3;
      else if (ch == 'L') d = (d + 3) & 3;
      else if (ch == 'S') swap(hand, cell[r][c]);
      else return false;
    }
    for (int i = 0;i < M;++i) if (cell[baskets[i].first][baskets[i].second] != i) return false;
    return true;
  }

}

int main() {
  ios::sync_with_stdio(false); cin.tie(nullptr);
  auto start = Clock::now();
  if (!(cin >> N >> M >> T)) return 0;
  vwall.resize(N); for (auto& s : vwall) cin >> s;
  hwall.resize(N - 1); for (auto& s : hwall) cin >> s;
  balls.resize(M); baskets.resize(M);
  for (int i = 0;i < M;++i) cin >> balls[i].first >> balls[i].second >> baskets[i].first >> baskets[i].second;
  points.push_back({ 0,0 });
  for (int i = 0;i < M;++i) { points.push_back(balls[i]);points.push_back(baskets[i]); }
  precompute();
  auto routes = optimize_routes(start);
  string best_raw, best_ctrl;
  int tried = 0;
  for (auto& rc : routes) {
    if (tried >= 3) break;
    ++tried;
    string raw = build_raw(rc.order);
    if (!raw_ok(raw)) continue;
    if (best_ctrl.empty() || raw.size() < best_ctrl.size()) { best_ctrl = raw;best_raw = raw; }
  }
  if (!best_raw.empty()) {
    auto nav = try_navigation_macros(best_raw, routes, start);
    if (!nav.first.empty()) {
      string expanded;
      if (expand_controller(nav.first, expanded) && raw_ok(expanded) && nav.first.size() < best_ctrl.size()) {
        best_ctrl = move(nav.first);best_raw = move(expanded);
      }
    }
  }
  if (!best_raw.empty() && chrono::duration<double>(Clock::now() - start).count() < 1.72) {
    string ctrl = beam_compress(best_raw, start), ex;
    if (expand_controller(ctrl, ex) && ex == best_raw && ctrl.size() < best_ctrl.size()) best_ctrl = move(ctrl);
  }
  if (best_ctrl.empty()) {
    vector<int> id(M); iota(id.begin(), id.end(), 0);
    best_raw = build_raw(id); best_ctrl = best_raw;
  }
  string ex;
  if (!expand_controller(best_ctrl, ex) || ex != best_raw || (int)best_ctrl.size() > T) best_ctrl = best_raw;
  // 制約上は通常不要だが、常に A <= T を保証する最終防衛線。
  if ((int)best_ctrl.size() > T) best_ctrl.resize(T);
  for (char ch : best_ctrl) cout << ch << '\n';
  return 0;
}
