vector<int> subset_conv(const vector<int>& f, const vector<int>& g, int B) {
  int M = 1 << B;
  vector<vector<int>> F(B + 1, vector<int>(M));
  vector<vector<int>> G(B + 1, vector<int>(M));
  vector<vector<int>> H(B + 1, vector<int>(M));
  for (int m = 0; m < M; m++) {
    int p = __builtin_popcount(m);
    F[p][m] = f[m];
    G[p][m] = g[m];
  }
  // Zeta transform (SOS) on each rank
  for (int k = 0; k <= B; k++)
    for (int b = 0; b < B; b++)
      for (int m = 0; m < M; m++)
        if (m >> b & 1) {
          F[k][m] = (F[k][m] + F[k][m ^ (1 << b)]) % MOD;
          G[k][m] = (G[k][m] + G[k][m ^ (1 << b)]) % MOD;
        }
  // Pointwise multiply over ranks
  for (int m = 0; m < M; m++)
    for (int k = 0; k <= B; k++)
      for (int i = 0; i <= k; i++)
        H[k][m] = (H[k][m] + (ll)F[i][m] * G[k - i][m]) % MOD;
  // Mobius transform (inverse zeta)
  for (int k = 0; k <= B; k++)
    for (int b = 0; b < B; b++)
      for (int m = 0; m < M; m++)
        if (m >> b & 1)
          H[k][m] = (H[k][m] - H[k][m ^ (1 << b)] + MOD) % MOD;
  vector<int> h(M);
  for (int m = 0; m < M; m++)
    h[m] = H[__builtin_popcount(m)][m];
  return h;
}
