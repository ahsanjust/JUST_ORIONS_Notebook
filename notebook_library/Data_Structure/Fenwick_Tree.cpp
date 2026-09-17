template <typename T>
struct BIT {
  int n;
  vector<T> bit;
  BIT(int n = 0) { init(n); }
  void init(int n_) {
    n = n_;
    bit.assign(n + 1, 0);
  }
  void add(int i, T v) {
    for (; i <= n; i += i & -i) bit[i] += v;
  }
  T sum(int i) {
    T r = 0;
    for (; i > 0; i -= i & -i) r += bit[i];
    return r;
  }
  T sum(int l, int r) { return sum(r) - sum(l - 1); }
  // returns smallest 1-based index with prefix sum >= k
  int find_kth(T k) {
    int i = 0;
    for (int j = 1 << (31 - __builtin_clz(n)); j; j >>= 1)
      if (i + j <= n && bit[i + j] < k) k -= bit[i += j];
    return i + 1;
  }
};
