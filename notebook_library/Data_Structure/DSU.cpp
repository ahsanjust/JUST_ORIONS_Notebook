struct dsu {
  vector<int> par, rank, sz;
  int cnt;
  dsu(int n) {
    par.resize(n);
    iota(par.begin(), par.end(), 0);
    rank.resize(n, 0);
    sz.resize(n, 1);
    cnt = n;
  }
  int find(int x) {
    return x == par[x] ? x : par[x] = find(par[x]);
  }
  bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y)
      return false;
    if (rank[x] < rank[y])
      swap(x, y);
    par[y] = x, sz[x] += sz[y];
    if (rank[x] == rank[y])
      rank[x] += 1;
    --cnt;
    return true;
  }
};
