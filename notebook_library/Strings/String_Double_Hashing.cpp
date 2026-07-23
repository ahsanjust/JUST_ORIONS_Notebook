struct DHash {
  ll mod[2] = {1000000007, 1000000009}, base[2] = {911382323, 972663749};
  vector<ll> pw[2], h[2];
  DHash(string &s) {
    int n = s.size();
    for (int k = 0; k < 2; k++) {
      pw[k].resize(n + 1, 1);
      h[k].resize(n + 1);
      for (int i = 0; i < n; i++) {
        pw[k][i + 1] = pw[k][i] * base[k] % mod[k];
        h[k][i + 1] = (h[k][i] * base[k] + s[i]) % mod[k];
      }
    }
  }
  pair<ll, ll> get(int l, int r) {
    return {
        (h[0][r + 1] - h[0][l] * pw[0][r - l + 1] % mod[0] + mod[0]) % mod[0],
        (h[1][r + 1] - h[1][l] * pw[1][r - l + 1] % mod[1] + mod[1]) % mod[1],
    };
  }
};
