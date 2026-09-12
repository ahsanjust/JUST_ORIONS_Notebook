void zeta_subset(vector<int64_t> &dp, int bits) {
  for (int b = 0; b < bits; b++)
    for (int mask = 0; mask < (1LL << bits); mask++)
      if (mask >> b & 1) dp[mask] += dp[mask ^ (1LL << b)];
}
void zeta_superset(vector<int64_t> &dp, int bits) {
  for (int b = 0; b < bits; b++)
    for (int mask = 0; mask < (1LL << bits); mask++)
      if (!(mask >> b & 1)) dp[mask] += dp[mask | (1LL << b)];
}
