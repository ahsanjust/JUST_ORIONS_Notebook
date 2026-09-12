struct Manacher {
  vector<int> p[2];
  Manacher(string s) {
    int n = s.size();
    p[0].resize(n + 1);  // even-len palindromes (right center)
    p[1].resize(n);      // odd-len palindromes (center at i)
    for (int z = 0; z < 2; z++) {
      for (int i = 0, l = 0, r = 0; i < n; i++) {
        int t = r - i + !z;
        if (i < r) p[z][i] = min(t, p[z][l + t]);
        int L = i - p[z][i], R = i + p[z][i] - !z;
        while (L >= 1 && R + 1 < n && s[L - 1] == s[R + 1]) p[z][i]++, L--, R++;
        if (R > r) l = L, r = R;  // update rightmost pal
      }
    }
  }
  bool is_pal(int l, int r) {
    int mid = (l + r + 1) / 2, len = r - l + 1;
    return 2 * p[len % 2][mid] + len % 2 >= len;
  }
};
