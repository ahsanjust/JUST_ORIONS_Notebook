struct HLD {
  int n, cur_pos = 1;
  vector<int> arr, parent, size, depth, heavy, head, pos;
  vector<vector<int>> adj;
  BIT<ll> segtree;
  HLD(int n)
      : n(n),
        arr(n + 1),
        parent(n + 1),
        size(n + 2),
        depth(n + 2),
        heavy(n + 2, 0),
        head(n + 2),
        pos(n + 2),
        adj(n + 2),
        segtree(BIT<ll>(n + 2)) {}
  void add_edge(int u, int v) {
    adj[u].push_back(v), adj[v].push_back(u);
  }
  void dfs(int u, int p) {
    parent[u] = p;
    size[u] = 1;
    int max_sz = 0;
    for (int v : adj[u]) {
      if (v == p)
        continue;
      depth[v] = depth[u] + 1;
      dfs(v, u);
      size[u] += size[v];
      if (size[v] > max_sz)
        max_sz = size[v], heavy[u] = v;
    }
  }
  void decompose(int u, int h) {
    head[u] = h;
    pos[u] = cur_pos++;
    segtree.add(pos[u], arr[u]);
    if (heavy[u])
      decompose(heavy[u], h);
    for (int v : adj[u])
      if (v != parent[u] && v != heavy[u])
        decompose(v, v);
  }
  int query(int u, int v) {
    int res = 0;
    while (head[u] != head[v]) {
      if (depth[head[u]] < depth[head[v]])
        swap(u, v);
      res += segtree.sum(pos[head[u]], pos[u]);
      u = parent[head[u]];
    }
    if (depth[u] > depth[v])
      swap(u, v);
    res += segtree.sum(pos[u], pos[v]);
    return res;
  }
  void addVal(int idx, int delta) {
    segtree.add(pos[idx], delta);
    arr[idx] += delta;
  }
  void editVal(int idx, int value) {
    segtree.add(pos[idx], value - arr[idx]);
    arr[idx] = value;
  }
};
