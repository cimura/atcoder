#include <bits/stdc++.h>
using namespace std;

namespace {

  using Clock = chrono::steady_clock;

  constexpr int INF = 1'000'000'000;

  int N;
  int M;
  int T;

  vector<string> v_walls;
  vector<string> h_walls;

  vector<pair<int, int>> balls;
  vector<pair<int, int>> baskets;

  /*
   * points[0]         : 初期位置 (0, 0)
   * points[1 + 2 * k] : 種類 k のボール
   * points[2 + 2 * k] : 種類 k のかご
   */
  vector<pair<int, int>> points;

  // 0: 右, 1: 下, 2: 左, 3: 上
  const int DR[4] = { 0, 1, 0, -1 };
  const int DC[4] = { 1, 0, -1, 0 };

  int state_count;
  int source_count;

  /*
   * 始点は「重要地点 + 向き」。
   * 終点は盤面上の全状態「マス + 向き」。
   */
  vector<vector<int>> dist_from;
  vector<vector<short>> parent_from;
  vector<vector<char>> action_from;

  int state_id(int r, int c, int dir) {
    return ((r * N + c) << 2) | dir;
  }

  void decode_state(int id, int& r, int& c, int& dir) {
    dir = id & 3;

    const int pos = id >> 2;
    r = pos / N;
    c = pos % N;
  }

  int source_id(int point_id, int dir) {
    return (point_id << 2) | dir;
  }

  bool can_move(int r, int c, int dir) {
    const int nr = r + DR[dir];
    const int nc = c + DC[dir];

    if (nr < 0 || nr >= N || nc < 0 || nc >= N) {
      return false;
    }

    if (dir == 0) {
      return v_walls[r][c] == '0';
    }

    if (dir == 1) {
      return h_walls[r][c] == '0';
    }

    if (dir == 2) {
      return v_walls[r][c - 1] == '0';
    }

    return h_walls[r - 1][c] == '0';
  }

  /*
   * 各重要地点・各開始方向から BFS する。
   *
   * 状態:
   *   (r, c, dir)
   *
   * 遷移:
   *   F, R, L
   */
  void precompute_paths() {
    state_count = N * N * 4;
    source_count = static_cast<int>(points.size()) * 4;

    dist_from.assign(
      source_count,
      vector<int>(state_count, INF)
    );

    parent_from.assign(
      source_count,
      vector<short>(state_count, -1)
    );

    action_from.assign(
      source_count,
      vector<char>(state_count, '?')
    );

    vector<int> queue_buffer(state_count);

    for (
      int point_id = 0;
      point_id < static_cast<int>(points.size());
      ++point_id
      ) {
      const auto [start_r, start_c] = points[point_id];

      for (int start_dir = 0; start_dir < 4; ++start_dir) {
        const int sid = source_id(point_id, start_dir);
        const int start_state = state_id(
          start_r,
          start_c,
          start_dir
        );

        int head = 0;
        int tail = 0;

        queue_buffer[tail++] = start_state;

        dist_from[sid][start_state] = 0;
        parent_from[sid][start_state] =
          static_cast<short>(start_state);

        auto push = [&](int from, int to, char action) {
          if (dist_from[sid][to] != INF) {
            return;
          }

          dist_from[sid][to] =
            dist_from[sid][from] + 1;

          parent_from[sid][to] =
            static_cast<short>(from);

          action_from[sid][to] = action;

          queue_buffer[tail++] = to;
          };

        while (head < tail) {
          const int current = queue_buffer[head++];

          int r;
          int c;
          int dir;

          decode_state(current, r, c, dir);

          /*
           * 同じ最短距離なら、直進を優先する。
           * 長い F の列が増えるため、マクロ圧縮にも多少有利。
           */
          if (can_move(r, c, dir)) {
            push(
              current,
              state_id(
                r + DR[dir],
                c + DC[dir],
                dir
              ),
              'F'
            );
          }

          push(
            current,
            state_id(r, c, (dir + 1) & 3),
            'R'
          );

          push(
            current,
            state_id(r, c, (dir + 3) & 3),
            'L'
          );
        }
      }
    }
  }

  int transition_cost(
    int from_point,
    int from_dir,
    int to_point,
    int to_dir
  ) {
    const auto [target_r, target_c] = points[to_point];

    return dist_from[source_id(from_point, from_dir)]
      [state_id(target_r, target_c, to_dir)];
  }

  /*
   * 現在地点から次の重要地点へ移動し、
   * 到着後に S を 1 回実行する。
   *
   * dp[dir]:
   *   現在地点に dir 向きでいるときの最小コスト
   */
  array<int, 4> move_dp(
    const array<int, 4>& dp,
    int from_point,
    int to_point
  ) {
    array<int, 4> next_dp;
    next_dp.fill(INF);

    for (int from_dir = 0; from_dir < 4; ++from_dir) {
      if (dp[from_dir] >= INF) {
        continue;
      }

      for (int to_dir = 0; to_dir < 4; ++to_dir) {
        const int distance = transition_cost(
          from_point,
          from_dir,
          to_point,
          to_dir
        );

        if (distance >= INF) {
          continue;
        }

        next_dp[to_dir] = min(
          next_dp[to_dir],
          dp[from_dir] + distance + 1
        );
      }
    }

    return next_dp;
  }

  /*
   * 指定された配送順の最小基本操作数を計算する。
   *
   * 各ボールについて、
   *   ボール位置へ移動 -> S
   *   かご位置へ移動   -> S
   * を行う。
   */
  int route_cost(const vector<int>& order) {
    array<int, 4> dp = { 0, INF, INF, INF };

    int current_point = 0;

    for (const int item : order) {
      const int ball_point = 1 + 2 * item;
      const int basket_point = 2 + 2 * item;

      dp = move_dp(dp, current_point, ball_point);
      current_point = ball_point;

      dp = move_dp(dp, current_point, basket_point);
      current_point = basket_point;
    }

    return *min_element(dp.begin(), dp.end());
  }

  /*
   * 貪欲法による初期解。
   *
   * candidate_width == 1:
   *   常に最も近いボールを選ぶ。
   *
   * candidate_width > 1:
   *   上位候補からランダムに選ぶ。
   *   焼きなまし法の初期解を多様化する。
   */
  vector<int> make_greedy_order(
    mt19937& random_engine,
    int candidate_width
  ) {
    vector<int> order;
    vector<char> used(M, false);

    order.reserve(M);

    array<int, 4> dp = { 0, INF, INF, INF };

    int current_point = 0;

    for (int step = 0; step < M; ++step) {
      struct Candidate {
        int cost;
        int item;
        int basket_point;
        array<int, 4> next_dp;
      };

      vector<Candidate> candidates;
      candidates.reserve(M - step);

      for (int item = 0; item < M; ++item) {
        if (used[item]) {
          continue;
        }

        const int ball_point = 1 + 2 * item;
        const int basket_point = 2 + 2 * item;

        const auto after_ball = move_dp(
          dp,
          current_point,
          ball_point
        );

        const auto after_basket = move_dp(
          after_ball,
          ball_point,
          basket_point
        );

        candidates.push_back(
          {
              *min_element(
                  after_basket.begin(),
                  after_basket.end()
              ),
              item,
              basket_point,
              after_basket
          }
        );
      }

      sort(
        candidates.begin(),
        candidates.end(),
        [](const Candidate& lhs, const Candidate& rhs) {
          if (lhs.cost != rhs.cost) {
            return lhs.cost < rhs.cost;
          }

          return lhs.item < rhs.item;
        }
      );

      const int width = min(
        candidate_width,
        static_cast<int>(candidates.size())
      );

      const int selected_index =
        width == 1
        ? 0
        : static_cast<int>(random_engine() % width);

      const auto& selected = candidates[selected_index];

      used[selected.item] = true;

      order.push_back(selected.item);

      dp = selected.next_dp;
      current_point = selected.basket_point;
    }

    return order;
  }

  struct RouteCandidate {
    int cost;
    vector<int> order;
  };

  void add_route_candidate(
    vector<RouteCandidate>& candidates,
    const vector<int>& order,
    int cost
  ) {
    for (const auto& candidate : candidates) {
      if (candidate.order == order) {
        return;
      }
    }

    candidates.push_back({ cost, order });

    sort(
      candidates.begin(),
      candidates.end(),
      [](const RouteCandidate& lhs, const RouteCandidate& rhs) {
        return lhs.cost < rhs.cost;
      }
    );

    constexpr int KEEP = 24;

    if (static_cast<int>(candidates.size()) > KEEP) {
      candidates.resize(KEEP);
    }
  }

  /*
   * 焼きなまし法による配送順の探索。
   *
   * 近傍:
   *   - 2 要素の swap
   *   - 区間 reverse
   *   - 1 要素の挿入移動
   */
  vector<RouteCandidate> optimize_order(
    const Clock::time_point& program_start
  ) {
    mt19937 random_engine(42);

    vector<RouteCandidate> candidates;

    vector<int> identity(M);
    iota(identity.begin(), identity.end(), 0);

    add_route_candidate(
      candidates,
      identity,
      route_cost(identity)
    );

    /*
     * 入力順以外の初期解も作る。
     */
    for (const int width : {1, 2, 2, 3, 3, 4}) {
      const auto order = make_greedy_order(
        random_engine,
        width
      );

      add_route_candidate(
        candidates,
        order,
        route_cost(order)
      );
    }

    vector<int> current_order = candidates.front().order;
    int current_cost = candidates.front().cost;

    vector<int> best_order = current_order;
    int best_cost = current_cost;

    /*
     * システムテストでは処理時間が少し伸びる可能性があるため、
     * 2 秒ぎりぎりまでは使わない。
     */
    constexpr double SEARCH_DEADLINE_SECONDS = 1.12;

    const double preprocessing_seconds =
      chrono::duration<double>(
        Clock::now() - program_start
      ).count();

    const double available_seconds = max(
      0.05,
      SEARCH_DEADLINE_SECONDS - preprocessing_seconds
    );

    const auto annealing_start = Clock::now();

    const double initial_temperature = max(
      6.0,
      best_cost * 0.018
    );

    constexpr double FINAL_TEMPERATURE = 0.18;

    uniform_real_distribution<double> random01(
      0.0,
      1.0
    );

    long long iterations = 0;

    while (true) {
      if ((iterations & 255) == 0) {
        const double total_elapsed =
          chrono::duration<double>(
            Clock::now() - program_start
          ).count();

        if (
          total_elapsed >=
          SEARCH_DEADLINE_SECONDS
          ) {
          break;
        }
      }

      const double elapsed =
        chrono::duration<double>(
          Clock::now() - annealing_start
        ).count();

      const double progress = min(
        1.0,
        elapsed / available_seconds
      );

      const double temperature =
        initial_temperature
        * pow(
          FINAL_TEMPERATURE
          / initial_temperature,
          progress
        );

      vector<int> next_order = current_order;

      int left =
        static_cast<int>(random_engine() % M);

      int right =
        static_cast<int>(random_engine() % M);

      if (left == right) {
        ++iterations;
        continue;
      }

      if (left > right) {
        swap(left, right);
      }

      const int operation =
        static_cast<int>(random_engine() % 10);

      if (operation < 4) {
        /*
         * swap
         */
        swap(
          next_order[left],
          next_order[right]
        );
      }
      else if (operation < 7) {
        /*
         * reverse
         */
        reverse(
          next_order.begin() + left,
          next_order.begin() + right + 1
        );
      }
      else {
        /*
         * insertion
         */
        const int value = next_order[left];

        next_order.erase(
          next_order.begin() + left
        );

        next_order.insert(
          next_order.begin() + right,
          value
        );
      }

      const int next_cost = route_cost(next_order);
      const int difference = next_cost - current_cost;

      const bool accept =
        difference <= 0
        || random01(random_engine)
        < exp(
          -static_cast<double>(difference)
          / temperature
        );

      if (accept) {
        current_order = std::move(next_order);
        current_cost = next_cost;

        if (current_cost < best_cost) {
          best_order = current_order;
          best_cost = current_cost;

          add_route_candidate(
            candidates,
            best_order,
            best_cost
          );
        }
        else if (
          (iterations & 4095) == 0
          && current_cost <= best_cost + 8
          ) {
          /*
           * 基本操作数は少し長くても、
           * 圧縮後は短くなる可能性がある。
           */
          add_route_candidate(
            candidates,
            current_order,
            current_cost
          );
        }
      }

      /*
       * 局所解に固まりすぎないように、
       * 良い既知解から探索を再開する。
       */
      if (
        (iterations & 32767) == 32767
        && candidates.size() >= 2
        && progress < 0.92
        ) {
        const int index = static_cast<int>(
          random_engine()
          % min<size_t>(
            candidates.size(),
            6
          )
          );

        current_order = candidates[index].order;
        current_cost = candidates[index].cost;
      }

      ++iterations;
    }

    add_route_candidate(
      candidates,
      best_order,
      best_cost
    );

    return candidates;
  }

  /*
   * BFS の親情報から、1 区間分の操作列を復元する。
   */
  string restore_segment(
    int from_point,
    int from_dir,
    int to_point,
    int to_dir
  ) {
    const int sid = source_id(
      from_point,
      from_dir
    );

    const auto [target_r, target_c] =
      points[to_point];

    int current = state_id(
      target_r,
      target_c,
      to_dir
    );

    const auto [start_r, start_c] =
      points[from_point];

    const int start = state_id(
      start_r,
      start_c,
      from_dir
    );

    string reversed_path;

    while (current != start) {
      const short parent =
        parent_from[sid][current];

      if (parent < 0) {
        return {};
      }

      reversed_path.push_back(
        action_from[sid][current]
      );

      current = parent;
    }

    reverse(
      reversed_path.begin(),
      reversed_path.end()
    );

    return reversed_path;
  }

  /*
   * 配送順に対応する最短基本操作列を復元する。
   *
   * 各地点への到着方向を DP で決めた後、
   * BFS の親情報をたどる。
   */
  string build_raw_commands(
    const vector<int>& order
  ) {
    vector<int> targets;
    targets.reserve(2 * M);

    for (const int item : order) {
      targets.push_back(1 + 2 * item);
      targets.push_back(2 + 2 * item);
    }

    vector<array<int, 4>> previous_direction(
      targets.size()
    );

    array<int, 4> dp = { 0, INF, INF, INF };

    int current_point = 0;

    for (
      int step = 0;
      step < static_cast<int>(targets.size());
      ++step
      ) {
      array<int, 4> next_dp;
      next_dp.fill(INF);

      previous_direction[step].fill(-1);

      const int target = targets[step];

      for (int from_dir = 0; from_dir < 4; ++from_dir) {
        if (dp[from_dir] >= INF) {
          continue;
        }

        for (int to_dir = 0; to_dir < 4; ++to_dir) {
          const int distance = transition_cost(
            current_point,
            from_dir,
            target,
            to_dir
          );

          if (distance >= INF) {
            continue;
          }

          const int value =
            dp[from_dir] + distance + 1;

          if (value < next_dp[to_dir]) {
            next_dp[to_dir] = value;
            previous_direction[step][to_dir] =
              from_dir;
          }
        }
      }

      dp = next_dp;
      current_point = target;
    }

    int final_direction = static_cast<int>(
      min_element(
        dp.begin(),
        dp.end()
      ) - dp.begin()
      );

    vector<int> end_direction(
      targets.size()
    );

    for (
      int step =
      static_cast<int>(targets.size()) - 1;
      step >= 0;
      --step
      ) {
      end_direction[step] = final_direction;

      final_direction =
        previous_direction[step][final_direction];
    }

    string raw_commands;

    raw_commands.reserve(
      *min_element(
        dp.begin(),
        dp.end()
      )
    );

    current_point = 0;

    int current_direction = 0;

    for (
      int step = 0;
      step < static_cast<int>(targets.size());
      ++step
      ) {
      raw_commands += restore_segment(
        current_point,
        current_direction,
        targets[step],
        end_direction[step]
      );

      raw_commands.push_back('S');

      current_point = targets[step];
      current_direction = end_direction[step];
    }

    return raw_commands;
  }

  /*
   * uint64_t のオーバーフローを利用したローリングハッシュ。
   *
   * 衝突確率は十分に低い。
   * 最終的には展開後の文字列一致も検証するため、
   * 仮に衝突しても不正な出力は採用しない。
   */
  struct RollingHash {
    static constexpr uint64_t BASE =
      1'000'003ULL;

    vector<uint64_t> power;
    vector<uint64_t> prefix;

    explicit RollingHash(const string& text) {
      power.resize(text.size() + 1);
      prefix.resize(text.size() + 1);

      power[0] = 1;

      for (
        size_t index = 0;
        index < text.size();
        ++index
        ) {
        power[index + 1] =
          power[index] * BASE;

        prefix[index + 1] =
          prefix[index] * BASE
          + static_cast<unsigned char>(
            text[index]
            )
          + 1;
      }
    }

    uint64_t get(
      int left,
      int right
    ) const {
      return prefix[right]
        - prefix[left] * power[right - left];
    }

    bool equal(
      int first,
      int second,
      int length
    ) const {
      return get(first, first + length)
        == get(second, second + length);
    }
  };

  /*
   * 新しいマクロを記録するとき、
   * 古い登録済みマクロを P で再利用する。
   *
   * 例:
   *   登録済みマクロ: FFF
   *   新規マクロ:     FFFFFFR
   *
   * 記録操作:
   *   MPPRM
   */
  string encode_body_with_old_macro(
    const string& raw_commands,
    int position,
    int length,
    const string& old_macro
  ) {
    string encoded_body;

    const int end = position + length;

    for (int index = position; index < end;) {
      if (
        !old_macro.empty()
        && index
        + static_cast<int>(old_macro.size())
        <= end
        && raw_commands.compare(
          index,
          old_macro.size(),
          old_macro
        ) == 0
        ) {
        encoded_body.push_back('P');

        index += static_cast<int>(
          old_macro.size()
          );
      }
      else {
        encoded_body.push_back(
          raw_commands[index]
        );

        ++index;
      }
    }

    return encoded_body;
  }

  /*
   * 現在の登録済みマクロを維持した場合に、
   * lookahead 内で何文字節約できるか概算する。
   */
  int estimate_registered_macro_gain(
    const string& raw_commands,
    int position,
    int end,
    const string& macro
  ) {
    if (macro.size() <= 1) {
      return 0;
    }

    const int length =
      static_cast<int>(macro.size());

    int gain = 0;

    for (
      int index = position;
      index + length <= end;
      ) {
      if (
        raw_commands.compare(
          index,
          length,
          macro
        ) == 0
        ) {
        gain += length - 1;
        index += length;
      }
      else {
        ++index;
      }
    }

    return gain;
  }

  struct CompressConfig {
    int max_macro_length;
    int lookahead;
    int replace_margin;
  };

  /*
   * 貪欲なマクロ圧縮。
   *
   * 現在位置から始まる部分列をマクロ候補とし、
   * 近い将来の再出現回数を調べる。
   *
   * 新しいマクロのほうが有利なら、
   *   M ... M
   * で登録する。
   *
   * 登録済みマクロが一致する場合は、
   *   P
   * で再生する。
   */
  string compress_greedy(
    const string& raw_commands,
    const CompressConfig& config
  ) {
    const int command_count =
      static_cast<int>(raw_commands.size());

    const RollingHash hash(raw_commands);

    string result;
    result.reserve(command_count);

    string registered_macro;

    for (int position = 0; position < command_count;) {
      const int end = min(
        command_count,
        position + config.lookahead
      );

      const int keep_gain =
        estimate_registered_macro_gain(
          raw_commands,
          position,
          end,
          registered_macro
        );

      int best_length = 0;
      int best_gain = INT_MIN;

      string best_encoded_body;

      const int length_limit = min(
        config.max_macro_length,
        command_count - position
      );

      for (
        int length = 2;
        length <= length_limit;
        ++length
        ) {
        int future_count = 0;

        for (
          int index = position + length;
          index + length <= end;
          ) {
          if (
            hash.equal(
              position,
              index,
              length
            )
            ) {
            ++future_count;
            index += length;
          }
          else {
            ++index;
          }
        }

        if (future_count == 0) {
          continue;
        }

        string encoded_body =
          encode_body_with_old_macro(
            raw_commands,
            position,
            length,
            registered_macro
          );

        /*
         * M + 本体 + M
         */
        const int definition_cost =
          static_cast<int>(
            encoded_body.size()
            )
          + 2;

        /*
         * マクロ未使用の場合との比較。
         *
         * 最初の 1 回:
         *   length - definition_cost
         *
         * 将来の再利用:
         *   1 回ごとに length - 1
         */
        const int gain =
          length
          - definition_cost
          + future_count * (length - 1);

        if (
          gain > best_gain
          || (
            gain == best_gain
            && length > best_length
            )
          ) {
          best_gain = gain;
          best_length = length;
          best_encoded_body =
            std::move(encoded_body);
        }
      }

      if (
        best_length > 0
        && best_gain
      > keep_gain
        + config.replace_margin
        ) {
        result.push_back('M');
        result += best_encoded_body;
        result.push_back('M');

        registered_macro = raw_commands.substr(
          position,
          best_length
        );

        position += best_length;

        continue;
      }

      if (
        !registered_macro.empty()
        && position
        + static_cast<int>(
          registered_macro.size()
          )
        <= command_count
        && raw_commands.compare(
          position,
          registered_macro.size(),
          registered_macro
        ) == 0
        ) {
        result.push_back('P');

        position += static_cast<int>(
          registered_macro.size()
          );
      }
      else {
        result.push_back(
          raw_commands[position]
        );

        ++position;
      }
    }

    return result;
  }

  /*
   * コントローラー操作列を基本操作列へ展開する。
   *
   * 展開結果が T を超えた場合は false。
   * 記録中のまま終了した場合も false。
   */
  bool expand_controller(
    const string& controller_commands,
    string& expanded_commands
  ) {
    expanded_commands.clear();

    string registered_macro;
    string recording_buffer;

    bool recording = false;

    for (const char command : controller_commands) {
      if (
        command == 'F'
        || command == 'R'
        || command == 'L'
        || command == 'S'
        ) {
        expanded_commands.push_back(command);

        if (recording) {
          recording_buffer.push_back(command);
        }
      }
      else if (command == 'M') {
        if (!recording) {
          recording = true;
          recording_buffer.clear();
        }
        else {
          recording = false;
          registered_macro = recording_buffer;
        }
      }
      else if (command == 'P') {
        expanded_commands += registered_macro;

        if (recording) {
          recording_buffer += registered_macro;
        }
      }
      else {
        return false;
      }

      if (
        expanded_commands.size()
          > static_cast<size_t>(T)
        ) {
        return false;
      }
    }

    return !recording;
  }

  /*
   * 基本操作列をシミュレーションし、
   * 全ボールが対応するかごへ入ったか確認する。
   */
  bool raw_delivers_everything(
    const string& raw_commands
  ) {
    if (
      raw_commands.size()
        > static_cast<size_t>(T)
      ) {
      return false;
    }

    vector<vector<int>> cell(
      N,
      vector<int>(N, -1)
    );

    for (int item = 0; item < M; ++item) {
      cell[balls[item].first]
        [balls[item].second] = item;
    }

    int r = 0;
    int c = 0;
    int dir = 0;

    int hand = -1;

    for (const char command : raw_commands) {
      if (command == 'F') {
        if (can_move(r, c, dir)) {
          r += DR[dir];
          c += DC[dir];
        }
      }
      else if (command == 'R') {
        dir = (dir + 1) & 3;
      }
      else if (command == 'L') {
        dir = (dir + 3) & 3;
      }
      else if (command == 'S') {
        swap(
          hand,
          cell[r][c]
        );
      }
      else {
        return false;
      }
    }

    for (int item = 0; item < M; ++item) {
      if (
        cell[baskets[item].first]
        [baskets[item].second]
        != item
        ) {
        return false;
      }
    }

    return true;
  }

  /*
   * 複数の圧縮パラメータを試し、
   * 最短の正しい操作列を採用する。
   */
  string compress_commands(
    const string& raw_commands,
    const Clock::time_point& program_start
  ) {
    string best_commands = raw_commands;

    const vector<CompressConfig> configs = {
        {24, 120, -1},
        {40, 180, 0},
        {64, 260, 1},
        {88, 380, 2},
    };

    for (const auto& config : configs) {
      const double elapsed =
        chrono::duration<double>(
          Clock::now() - program_start
        ).count();

      /*
       * 圧縮処理でも 2 秒ぎりぎりまで使わない。
       */
      if (elapsed >= 1.70) {
        break;
      }

      string candidate = compress_greedy(
        raw_commands,
        config
      );

      if (
        candidate.size()
        >= best_commands.size()
        ) {
        continue;
      }

      string expanded_commands;

      if (
        expand_controller(
          candidate,
          expanded_commands
        )
        && expanded_commands == raw_commands
        ) {
        best_commands = std::move(candidate);
      }
    }

    return best_commands;
  }

} // namespace

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  const auto program_start = Clock::now();

  if (!(cin >> N >> M >> T)) {
    return 0;
  }

  v_walls.resize(N);

  for (auto& row : v_walls) {
    cin >> row;
  }

  h_walls.resize(N - 1);

  for (auto& row : h_walls) {
    cin >> row;
  }

  balls.resize(M);
  baskets.resize(M);

  for (int item = 0; item < M; ++item) {
    cin
      >> balls[item].first
      >> balls[item].second
      >> baskets[item].first
      >> baskets[item].second;
  }

  points.reserve(1 + 2 * M);

  points.push_back({ 0, 0 });

  for (int item = 0; item < M; ++item) {
    points.push_back(balls[item]);
    points.push_back(baskets[item]);
  }

  /*
   * 1. 向きを含めた最短経路の事前計算
   */
  precompute_paths();

  /*
   * 2. 焼きなまし法で配送順を探索
   */
  const auto route_candidates =
    optimize_order(program_start);

  string best_raw_commands;
  string best_controller_commands;

  /*
   * 3. 良い配送順を複数個試し、
   *    圧縮後のボタン操作数で比較する
   */
  int checked_routes = 0;

  for (const auto& candidate : route_candidates) {
    if (checked_routes >= 8) {
      break;
    }

    const double elapsed =
      chrono::duration<double>(
        Clock::now() - program_start
      ).count();

    if (
      checked_routes > 0
      && elapsed >= 1.72
      ) {
      break;
    }

    ++checked_routes;

    string raw_commands =
      build_raw_commands(candidate.order);

    if (
      !raw_delivers_everything(
        raw_commands
      )
      ) {
      continue;
    }

    string controller_commands =
      compress_commands(
        raw_commands,
        program_start
      );

    string expanded_commands;

    if (
      !expand_controller(
        controller_commands,
        expanded_commands
      )
      || expanded_commands != raw_commands
      ) {
      continue;
    }

    if (
      controller_commands.size()
  > static_cast<size_t>(T)
      ) {
      continue;
    }

    if (
      best_controller_commands.empty()
      || controller_commands.size()
      < best_controller_commands.size()
      ) {
      best_raw_commands =
        std::move(raw_commands);

      best_controller_commands =
        std::move(controller_commands);
    }
  }

  /*
   * 通常は到達しない。
   * 念のため入力順をフォールバックにする。
   */
  if (best_controller_commands.empty()) {
    vector<int> identity(M);

    iota(
      identity.begin(),
      identity.end(),
      0
    );

    best_raw_commands =
      build_raw_commands(identity);

    best_controller_commands =
      best_raw_commands;
  }

  /*
   * 最終防衛線。
   * 圧縮列が壊れていた場合は、
   * 圧縮前の基本操作列を出力する。
   */
  string expanded_commands;

  if (
    !expand_controller(
      best_controller_commands,
      expanded_commands
    )
    || expanded_commands != best_raw_commands
    || best_controller_commands.size()
      > static_cast<size_t>(T)
    ) {
    best_controller_commands =
      best_raw_commands;
  }

  for (
    const char command :
  best_controller_commands
    ) {
    cout << command << '\n';
  }

  return 0;
}
