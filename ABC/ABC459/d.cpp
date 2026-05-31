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

int func(int n) {
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans += (n - i + 1);
  }
  //cout << "ans: " << ans << endl;
  return ans;
}

// 実行時に変数名も表示するマクロ
#define debug(...) std::cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)

int main() {
  int t; cin >> t;
  while (t--) {
    map<char, int> mp;
    string s; cin >> s;
    for (char c : s) {
      mp[c]++;
    }
    vector<pair<char, int>> vp(mp.begin(), mp.end());
    sort(vp.begin(), vp.end(), [](const auto& a, const auto& b) {
      return a.second > b.second;
      });

    string ans(s.length(), '?');
    for (int i = 0; i < vp.size(); ++i) {
      char c = vp[i].first;
      int cnt = vp[i].second;
      int idx = 0;
      while (cnt > 0 && idx < s.length()) {
        if (ans[idx] == '?') {
          ans[idx] = c;
          idx += 2;
          cnt--;
        }
        else {
          idx++;
        }
      }
    }
    if (ans.contains("?")) {
      cout << "No" << endl;
    }
    else {
      cout << "Yes" << endl;
      cout << ans << endl;
    }
  }
}
