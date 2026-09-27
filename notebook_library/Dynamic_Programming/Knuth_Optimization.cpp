for (int i = 0; i <= n; i++) {
  p[i][i] = i, dp[i][i] = 0;
  if (i < n) dp[i][i + 1] = cost(i, i + 1), p[i][i + 1] = i;
}
for (int len = 2; len <= n; len++) {
  for (int i = 0; i + len <= n; i++) {
    int j = i + len;
    dp[i][j] = LLONG_MAX;
    for (int k = p[i][j - 1]; k <= p[i + 1][j]; k++) {
      ll val = dp[i][k] + dp[k][j] + cost(i, j);
      if (val < dp[i][j]) { dp[i][j] = val; p[i][j] = k; }
    }
  }
}
