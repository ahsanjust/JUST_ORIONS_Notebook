struct Trie {
  static const int B = 31;
  struct Node {
    int nxt[2];
    int cnt;
  };
  vector<Node> pool;
  Trie() { pool.push_back({0, 0, 0}); }
  void add(int x, int v = 1) {
    int u = 0;
    pool[u].cnt += v;
    for (int i = B - 1; i >= 0; --i) {
      int d = (x >> i) & 1;
      if (!pool[u].nxt[d]) {
        pool[u].nxt[d] = pool.size();
        pool.push_back({0, 0, 0});
      }
      u = pool[u].nxt[d];
      pool[u].cnt += v;
    }
  }
  int count(int x) {
    int u = 0;
    for (int i = B - 1; i >= 0; --i) {
      int d = (x >> i) & 1;
      int nxt = pool[u].nxt[d];
      if (!nxt || !pool[nxt].cnt) return 0;
      u = nxt;
    }
    return pool[u].cnt;
  }
  int count_xor_less(int x, int k) {
    int u = 0, ans = 0;
    for (int i = B - 1; i >= 0; --i) {
      int d = (x >> i) & 1;
      if ((k >> i) & 1) {
        if (pool[u].nxt[d]) ans += pool[pool[u].nxt[d]].cnt;
        if (!pool[u].nxt[d ^ 1]) break;
        u = pool[u].nxt[d ^ 1];
      } else {
        if (!pool[u].nxt[d]) break;
        u = pool[u].nxt[d];
      }
    }
    return ans;
  }
  int count_xor_greater(int x, int k) {
    if (k >= (1LL << B) - 1) return 0;
    return pool[0].cnt - count_xor_less(x, k + 1);
  }
  int get_kth(int k) {
    if (pool[0].cnt < k) return -1;
    int u = 0, ans = 0;
    for (int i = B - 1; i >= 0; --i) {
      int left = pool[u].nxt[0] ? pool[pool[u].nxt[0]].cnt : 0;
      if (k <= left) u = pool[u].nxt[0];
      else k -= left, u = pool[u].nxt[1], ans |= (1 << i);
    }
    return ans;
  }
  int get_xor_kth(int x, int k) {
    if (pool[0].cnt < k) return -1;
    int u = 0, ans = 0;
    for (int i = B - 1; i >= 0; --i) {
      int d = (x >> i) & 1;
      int req = pool[u].nxt[d] ? pool[pool[u].nxt[d]].cnt : 0;
      if (k <= req) u = pool[u].nxt[d];
      else k -= req, u = pool[u].nxt[d ^ 1], ans |= (1 << i);
    }
    return ans;
  }
  int64_t go(int u, int b, int x, int t1, int t2) {
    if (!t1 || t2 == 2) return 0;
    if ((t1 == 2 && !t2) || b < 0) return pool[u].cnt;
    int d = (x >> b) & 1;
    int64_t res = 0;
    if (d) {
      if (pool[u].nxt[1]) res += go(pool[u].nxt[1], b - 1, x, t1 == 1 ? 0 : t1, t2 == 1 ? 0 : t2);
      if (pool[u].nxt[0]) res += go(pool[u].nxt[0], b - 1, x, t1 == 1 ? 2 : t1, t2);
    } else {
      if (pool[u].nxt[1]) res += go(pool[u].nxt[1], b - 1, x, t1, t2 == 1 ? 2 : t2);
      if (pool[u].nxt[0]) res += go(pool[u].nxt[0], b - 1, x, t1, t2);
    }
    return res;
  }
  int64_t count_special(int x) { return go(0, B - 1, x, 1, 1); }
};
