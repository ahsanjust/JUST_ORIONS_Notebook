struct WT {
  int lo, hi;
  vector<int> b;
  WT *l = 0, *r = 0;
  WT(vector<int> &v, int lo, int hi) : lo(lo), hi(hi) {
    if (v.empty() || lo + 1 == hi)
      return;
    int mid = (lo + hi) / 2;
    b.resize(v.size() + 1);
    for (int i = 0; i < (int)v.size(); i++)
      b[i + 1] = b[i] + (v[i] < mid);
    auto p = stable_partition(v.begin(), v.end(), [&](int x) { return x < mid; }) - v.begin();
    vector<int> vl(v.begin(), v.begin() + p);
    vector<int> vr(v.begin() + p, v.end());
    l = new WT(vl, lo, mid);
    r = new WT(vr, mid, hi);
  }
  int kth(int k, int L, int R) {
    if (lo + 1 == hi)
      return lo;
    int left = b[R + 1] - b[L];
    if (k < left)
      return l->kth(k, b[L], b[R + 1] - 1);
    else
      return r->kth(k - left, L - b[L], R - b[R + 1]);
  }
  int count_leq(int L, int R, int x) {
    if (L > R || x < lo)
      return 0;
    if (x >= hi - 1)
      return R - L + 1;
    if (lo + 1 == hi)
      return 0;
    int mid = (lo + hi) / 2;
    if (x < mid)
      return l->count_leq(b[L], b[R + 1] - 1, x);
    else
      return (b[R + 1] - b[L]) + r->count_leq(L - b[L], R - b[R + 1], x);
  }
  int count_seg(int L, int R, int x, int y) {
    if (x > y)
      return 0;
    return count_leq(L, R, y) - count_leq(L, R, x - 1);
  }
};
