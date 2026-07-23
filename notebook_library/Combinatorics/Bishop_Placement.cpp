int bishop_placements(int N, int K) {
  if (K > 2 * N - 1)
    return 0;
  auto len = [&](int i) {
    if (i > N)
      return 2 * N - i;
    return i;
  };
  // Collect diagonal lengths for each color, sorted increasingly
  vector<int> black, white;
  for (int i = 1; i <= 2 * N - 1; i++) {
    if (i & 1)
      black.push_back(len(i));
    else
      white.push_back(len(i));
  }
  sort(black.begin(), black.end());
  sort(white.begin(), white.end());
  auto solve = [&](vector<int> &diag, int K) {
    int m = diag.size();
    vector<vector<int>> D(m + 1, vector<int>(K + 1, 0));
    D[0][0] = 1;
    for (int i = 1; i <= m; i++)
      for (int j = 0; j <= K; j++) {
        D[i][j] = D[i - 1][j];
        if (j > 0)
          D[i][j] += D[i - 1][j - 1] * (diag[i - 1] - j + 1);
      }
    return D[m];
  };
  auto B = solve(black, K), W = solve(white, K);
  int ans = 0;
  for (int i = 0; i <= K; i++)
    ans += B[i] * W[K - i];
  return ans;
}
