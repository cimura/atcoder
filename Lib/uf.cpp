#include <iostream>
#include <vector>

using namespace std;

struct UnionFind {
  vector<int> parent;

  UnionFind(int n) : parent(n, -1) {}

  int root(int x) {
    if (parent[x] < 0) return x;
    return parent[x] = root(parent[x]);
  }

  bool unite(int x, int y) {
    int rx = root(x);
    int ry = root(y);
    if (rx == ry) return false;

    if (parent[rx] > parent[ry]) swap(rx, ry);
    parent[rx] += parent[ry];
    parent[ry] = rx;
    return true;
  }

  bool same(int x, int y) {
    return root(x) == root(y);
  }
};

#ifdef BUILD_MAIN

int main() {
  // 入出力の高速化（データ数が多いので必須！）
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, q;
  if (!(cin >> n >> q)) return 0;

  // 0 から N-1 までの UnionFind を作成
  UnionFind uf(n);

  for (int i = 0; i < q; ++i) {
    int p, a, b;
    cin >> p >> a >> b;

    if (p == 0) {
      // 結合操作（グループをまとめる）
      uf.unite(a, b);
    }
    else {
      // 判定操作（同じグループか調べる）
      if (uf.same(a, b)) {
        cout << "Yes\n";
      }
      else {
        cout << "No\n";
      }
    }
  }

  return 0;
}

#endif
