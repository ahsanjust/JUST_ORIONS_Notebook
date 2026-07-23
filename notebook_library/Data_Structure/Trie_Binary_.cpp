struct Trie {
  static const int B = 31;
  vector<array<int, 2>> nxt;
  vector<int> cnt;
  Trie() {
    nxt.push_back({0, 0});
    cnt.push_back(0);
  }
  void add(int x, int v = 1) {
    int u = 0;
    cnt[u] += v;
    for (int i = B - 1; i >= 0; --i) {
      int d = (x >> i) & 1;
      if (!nxt[u][d]) {
        nxt[u][d] = nxt.size();
        nxt.push_back({0, 0});
        cnt.push_back(0);
      }
      u = nxt[u][d];
      cnt[u] += v;
    }
  }
  int count(int x) {
    int u = 0;
    for (int i = B - 1; i >= 0; --i) {
      int d = (x >> i) & 1;
      if (!nxt[u][d] || !cnt[nxt[u][d]])
        return 0;
      u = nxt[u][d];
    }
    return cnt[u];
  }
  int count_xor_less(int x, int k) {
    int u = 0, ans = 0;
    for (int i = B - 1; i >= 0; --i) {
      int d = (x >> i) & 1;
      if ((k >> i) & 1) {
        if (nxt[u][d])
          ans += cnt[nxt[u][d]];
        if (!nxt[u][d ^ 1])
          break;
        u = nxt[u][d ^ 1];
      } else {
        if (!nxt[u][d])
          break;
        u = nxt[u][d];
      }
    }
    return ans;
  }
  int count_xor_greater(int x, int k) {
    if (k >= (1LL << B) - 1)
      return 0;
    return cnt[0] - count_xor_less(x, k + 1);
  }
  int get_kth(int k) {
    if (cnt[0] < k)
      return -1;
    int u = 0, ans = 0;
    for (int i = B - 1; i >= 0; --i) {
      int left = nxt[u][0] ? cnt[nxt[u][0]] : 0;
      if (k <= left)
        u = nxt[u][0];
      else
        k -= left, u = nxt[u][1], ans |= (1 << i);
    }
    return ans;
  }
  int get_xor_kth(int x, int k) {
    if (cnt[0] < k)
      return -1;
    int u = 0, ans = 0;
    for (int i = B - 1; i >= 0; --i) {
      int d = (x >> i) & 1;
      int req = nxt[u][d] ? cnt[nxt[u][d]] : 0;
      if (k <= req)
        u = nxt[u][d], ans |= (0 << i);
      else
        k -= req, u = nxt[u][d ^ 1], ans |= (1 << i);
    }
    return ans;
  }
  int64_t go(int u, int b, int x, int t1, int t2) {
    if (!t1 || t2 == 2)
      return 0;
    if ((t1 == 2 && !t2) || b < 0)
      return cnt[u];
    int d = (x >> b) & 1;
    int64_t res = 0;
    if (d) {
      if (nxt[u][1])
        res += go(nxt[u][1], b - 1, x, t1 == 1 ? 0 : t1, t2 == 1 ? 0 : t2);
      if (nxt[u][0])
        res += go(nxt[u][0], b - 1, x, t1 == 1 ? 2 : t1, t2);
    } else {
      if (nxt[u][1])
        res += go(nxt[u][1], b - 1, x, t1, t2 == 1 ? 2 : t2);
      if (nxt[u][0])
        res += go(nxt[u][0], b - 1, x, t1, t2);
    }
    return res;
  }
  int64_t count_special(int x) {
    return go(0, B - 1, x, 1, 1);
  }
};
