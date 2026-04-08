#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int N = 3; // 荷物の数
    int W = 15; // ナップザックの最大容量
    std::vector<int> weight = {10, 7, 8};
    std::vector<int> value = {100, 70, 80};

    // dp[i][w] : i番目までの荷物を見て、重さ合計がw以下の時の最大価値
    std::vector<std::vector<int>> dp(N + 1, std::vector<int>(W + 1, 0));

    for (int i = 0; i < N; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (w >= weight[i]) {
                // 「入れる」か「入れない」か、価値が高い方を採用
                dp[i + 1][w] = std::max(dp[i][w], dp[i][w - weight[i]] + value[i]);
            } else {
				std::cout << "w: " << w << std::endl;
                // 入らないので、前の状態を引き継ぐ
                dp[i + 1][w] = dp[i][w];
            }
        }
    }

    std::cout << "最大価値: " << dp[N][W] << std::endl;
    return 0;
}