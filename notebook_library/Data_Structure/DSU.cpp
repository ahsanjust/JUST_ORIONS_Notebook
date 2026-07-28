struct dsu {
  vector<int> e;  // negative = size (root), non-negative = parent
  int cnt;
  dsu(int n) : e(n, -1), cnt(n) {}
  int find(int x) {
    return e[x] < 0 ? x : e[x] = find(e[x]);
  }
  bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y)
      return false;
    if (e[x] > e[y])
      swap(x, y);  // more negative = larger size
    e[x] += e[y];
    e[y] = x;
    --cnt;
    return true;
  }
  int size(int x) { return -e[find(x)]; }
};
