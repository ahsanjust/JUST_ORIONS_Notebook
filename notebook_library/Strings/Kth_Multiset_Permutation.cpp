string kth(vector<int> f, int n, ll k) {
  if (k < 1) return "";
  string s;
  for (int i = 0; i < n; i++) {
    for (int c = 0; c < (int)f.size(); c++)
      if (f[c]) {
        f[c]--;
        ll w = 1;
        int r = n - i - 1;
        for (int d : f)
          if (d) {
            ll cm = 1;
            int m = min(d, r - d);
            for (int j = 1; j <= m; j++) cm = cm * (r - m + j) / j;
            w *= cm;
            if (w > k) break;
            r -= d;
          }
        if (w >= k) {
          s += 'a' + c;
          break;
        }
        k -= w;
        f[c]++;
      }
    if ((int)s.size() <= i) return "";
  }
  return s;
}
