weight = [10, 7, 8]
value = [100, 70, 80]

N = 3
W = 15

dp = [[0] * (W+1) for _ in range(N+1)]

def loop_knap():
	for i in range(0, N):
		for w in range(0, W+1):
			if w >= weight[i]:
				dp[i+1][w] = max(dp[i][w], dp[i][w-weight[i]]+value[i])
			else:
				dp[i+1][w] = dp[i][w]


loop_knap()
print(f"Result: {dp[N][W]}")