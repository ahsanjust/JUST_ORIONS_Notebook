vector<int> getBorderCnt(const vector<int> &pi, bool proper = false) {
  int m = pi.size();
  vector<int> dp(m + 1, 0);
  for (int len = 1; len <= m; len++) {
    if (proper && len == m) dp[m] = dp[pi[m - 1]];
    else dp[len] = 1 + dp[pi[len - 1]];
  }
  return dp;
}
