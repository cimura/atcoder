# ABC457 振り返りレポート

## コンテスト概要
- コンテスト: AtCoder Beginner Contest 457
- 実施日: 2026/5/9
- AB2完

## 各問題の結果と振り返り

### A問題
**実装内容**: 配列のx番目の要素を出力する基本問題

**コード**: a.cpp:18
```cpp
cout << a[x-1] << endl;
```

**振り返り**:
- 1-indexedから0-indexedへの変換を正しく処理できた
- 基本的な配列アクセス問題として適切に解決

---

### B問題
**実装内容**: ジャグ配列（可変長2次元配列）のx行y列目の要素を出力

**コード**: b.cpp:13-23
```cpp
vector<vector<int>> v(n);
rep(i, n) {
    int l; cin >> l;
    vi a(l);
    rep(j, l) {
        cin >> a[j];
    }
    v[i] = a;
}
int x, y; cin >> x >> y;
cout << v[x-1][y-1] << endl;
```

**振り返り**:
- ジャグ配列の実装が適切にできた
- 1-indexedから0-indexedへの変換も問題なし

---

### C問題
**実装内容**: グループ化された配列からk番目の要素を見つける問題

**試行錯誤**:
- 累積サイズを計算せずに、現在のkから引いていくアプローチ （推奨）
- 累積サイズを計算して、範囲判定するアプローチ

**サイズを保存しておくアプローチ** (非推奨、本番はこのやり方でやったため失敗):
```cpp
rep(i, n) {
    ll c; cin >> c;
    container_size += (ll)c * vv[i].size();
    if (container_size >= k) {
      int idx = (k - prev_size - 1) % vv[i].size();
      cout << vv[i][idx] << endl;
      return 0;
    }
    prev_size = container_size;
  }
```
**kから引いていくアプローチ** (推奨):
```cpp
ll current_k = k;
rep(i, n) {
    ll c; cin >> c;
    ll current_group_size = (ll)c * vv[i].size();
    if (current_group_size >= current_k) {
        int idx = (current_k - 1) % vv[i].size();
        cout << vv[i][idx] << endl;
        return 0;
    }
    current_k -= current_group_size;
}
```

**振り返り**:
- c.cppの方が論理的にシンプルで理解しやすい（残りのkを追跡）
- long longを使わなかったことでWAしていた

**学んだこと**:
- グループごとに繰り返されるパターンからk番目を見つける問題では、剰余演算が鍵
- current_kを減算していくアプローチの方が実装ミスが少ない

---

### D問題
**実装内容**: ソートとスワップを使った問題（未完成）

**コード**: d.cpp:69-83
```cpp
int n, k; cin >> n >> k;
vector<pair<int, ll>> vp(n);
rep(i, n) {
    int a; cin >> a;
    vp[i] = { i,a };
}
sort(vp.begin(), vp.end());

int ai = 0;
while (1) {
    vp[ai].second += ai + 1;
    if (vp[ai+1].second < vp[ai].second) swap(vp[ai+1], vp[ai]);
}
```

**問題点**:
- 無限ループになっている（終了条件がない）
- 配列の境界チェックがない（ai+1が範囲外になる可能性）
- アルゴリズムの方針が不明確

**振り返り**:
- D問題は時間内に完成できなかった
- 問題の本質を理解する前に実装を始めてしまった可能性
- アルゴリズムの設計段階でもう少し時間をかけるべきだった

**改善点**:
- 問題を読んだ後、サンプルケースで手動トレースしてパターンを見つける
- アルゴリズムの正当性を確認してから実装する
- エッジケースと終了条件を先に考える

---

## 総合評価

### 良かった点
1. A, B問題を確実に解けた

### 改善が必要な点
1. 無限ループや配列の境界チェック漏れ

### 今後の学習課題
1. より難易度の高い問題でのアルゴリズム設計力の向上
2. 実装前の設計段階での思考時間の確保
3. エッジケースと終了条件の体系的なチェック

## まとめ
ABC程度のA, B問題は安定して解けるレベルに達している。C問題以降の難易度で時間内に完成させるためには、アルゴリズムの設計段階での思考の質を高める必要がある。
