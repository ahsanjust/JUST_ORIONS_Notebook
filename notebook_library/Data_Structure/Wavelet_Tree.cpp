struct WT {
  int n, lg;
  vector<vector<uint64_t>> b;
  vector<vector<int>> p; // prefix sum over 64-bit blocks
  vector<int> z;         // number of 0s at each level
  WT(vector<int> v) : n(v.size()) {
    int mx = n ? *max_element(v.begin(), v.end()) : 0;
    lg = mx ? 32 - __builtin_clz(mx) : 0;
    if (!lg) { b.resize(1); p.resize(1); z.resize(1); return; }
    b.resize(lg); p.resize(lg); z.resize(lg);
    vector<int> cur = v, nxt(n);
    for (int d = lg - 1; d >= 0; --d) {
      int bc = (n + 63) / 64;
      b[d].assign(bc, 0);
      int p0 = 0, p1 = 0;
      for (int i = 0; i < n; ++i) {
        if (cur[i] >> d & 1) {
          b[d][i / 64] |= 1ULL << (i % 64);
          nxt[p1++] = cur[i];
        } else cur[p0++] = cur[i];
      }
      z[d] = p0;
      copy(nxt.begin(), nxt.begin() + p1, cur.begin() + p0);
      p[d].resize(bc + 1);
      for (int i = 0; i < bc; ++i)
        p[d][i + 1] = p[d][i] + __builtin_popcountll(b[d][i]);
    }
  }
  int rank1(int d, int i) const {
    int bc = (n + 63) / 64;
    if (i >= n) return p[d][bc];
    int r = i / 64;
    return p[d][r] + __builtin_popcountll(
      b[d][r] & ((1ULL << (i % 64)) - 1));
  }
  int rank0(int d, int i) const { return i - rank1(d, i); }
  int kth(int l, int r, int k) {
    int ans = 0;
    for (int d = lg - 1; d >= 0; --d) {
      int c0 = rank0(d, r) - rank0(d, l);
      if (k < c0) {
        l = rank0(d, l); r = rank0(d, r);
      } else {
        ans |= 1 << d; k -= c0;
        l = z[d] + rank1(d, l); r = z[d] + rank1(d, r);
      }
    }
    return ans;
  }
  int count_leq(int l, int r, int x) {
    if (x < 0) return 0;
    if (r <= l) return 0;
    if (x >= (1LL << lg)) return r - l;
    int ans = 0;
    for (int d = lg - 1; d >= 0; --d) {
      int c0 = rank0(d, r) - rank0(d, l);
      if (x >> d & 1) {
        ans += c0;
        l = z[d] + rank1(d, l); r = z[d] + rank1(d, r);
      } else {
        l = rank0(d, l); r = rank0(d, r);
      }
    }
    return ans + (r - l);
  }
  int count_seg(int l, int r, int x, int y) {
    if (x > y) return 0;
    return count_leq(l, r, y) - count_leq(l, r, x - 1);
  }
};
