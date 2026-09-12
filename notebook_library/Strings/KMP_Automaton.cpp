const int K = 26;
vector<array<int, K>> buildAuto(const string &s) {
  auto pi = getLps(s);
  int n = s.size();
  vector<array<int, K>> nxt(n + 1);
  nxt[0][s[0] - 'a'] = 1;
  for (int i = 1; i <= n; i++)
    for (int c = 0; c < K; c++) {
      if (i == n || c != s[i] - 'a') nxt[i][c] = nxt[pi[i - 1]][c];
      else nxt[i][c] = i + 1;
    }
  return nxt;
}
