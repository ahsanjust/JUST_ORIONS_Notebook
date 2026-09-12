struct LCA {
  int n, LOG;
  vector<vector<int>> adj, up;
  vector<int> depth;
  LCA(int _n) : n(_n), LOG(__lg(_n) + 2), adj(_n), up(_n, vector<int>(LOG, -1)), depth(_n, 0) {}
  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  void dfs(int u, int p = -1, int d = 0) {
    up[u][0] = p;
    depth[u] = d;
    for (int i = 1; i < LOG; i++) {
      if (up[u][i - 1] != -1) up[u][i] = up[up[u][i - 1]][i - 1];
    }
    for (int v : adj[u])
      if (v != p) dfs(v, u, d + 1);
  }
  int lift(int u, int k) {
    for (int i = 0; i < LOG; i++) {
      if ((k >> i) & 1) u = up[u][i];
      if (u == -1) break;
    }
    return u;
  }
  int query(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    u = lift(u, depth[u] - depth[v]);
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; i--) {
      if (up[u][i] != up[v][i]) {
        u = up[u][i];
        v = up[v][i];
      }
    }
    return up[u][0];
  }
};
