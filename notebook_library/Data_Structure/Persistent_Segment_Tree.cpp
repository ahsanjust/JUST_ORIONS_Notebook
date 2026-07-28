struct PST {
  static const int N = 2'00'000;
  static const int LG = 18;
  static const int M = 1 + 4 * N + N * LG;
  int lc[M], rc[M], val[M];
  int sz = 1;

  int build(int b, int e) {
    int cur = sz++;
    if (b == e) return cur;
    int m = (b + e) >> 1;
    lc[cur] = build(b, m);
    rc[cur] = build(m + 1, e);
    return cur;
  }
  int upd(int pre, int b, int e, int i, int v) {
    int cur = sz++;
    lc[cur] = lc[pre];
    rc[cur] = rc[pre];
    if (b == e) { val[cur] = val[pre] + v; return cur; }
    int m = (b + e) >> 1;
    if (i <= m) lc[cur] = upd(lc[pre], b, m, i, v);
    else        rc[cur] = upd(rc[pre], m + 1, e, i, v);
    val[cur] = val[lc[cur]] + val[rc[cur]];
    return cur;
  }
  int kth(int pre, int cur, int b, int e, int k) {
    while (b < e) {
      int m = (b + e) >> 1;
      int left_cnt = val[lc[cur]] - val[lc[pre]];
      if (k <= left_cnt) { cur = lc[cur]; pre = lc[pre]; e = m; }
      else               { cur = rc[cur]; pre = rc[pre]; b = m + 1; k -= left_cnt; }
    }
    return b;
  }
  int cnt(int pre, int cur, int b, int e, int x) {
    if (x < b) return 0;
    int res = 0;
    while (b < e) {
      int m = (b + e) >> 1;
      if (x <= m) { cur = lc[cur]; pre = lc[pre]; e = m; }
      else { res += val[lc[cur]] - val[lc[pre]]; cur = rc[cur]; pre = rc[pre]; b = m + 1; }
    }
    res += val[cur] - val[pre];
    return res;
  }
  int sum(int pre, int cur, int b, int e, int l, int r) {
    if (l > e || r < b) return 0;
    if (l <= b && e <= r) return val[cur] - val[pre];
    int m = (b + e) >> 1;
    return sum(lc[pre], lc[cur], b, m, l, r) + sum(rc[pre], rc[cur], m + 1, e, l, r);
  }
};
