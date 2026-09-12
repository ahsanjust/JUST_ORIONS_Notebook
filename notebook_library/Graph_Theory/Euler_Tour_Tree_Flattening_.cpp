struct EulerTour {
  int n, timer;
  vector<vector<int>> adj;
  vector<int> in, out, flat;
  EulerTour(int _n) : n(_n), timer(0), adj(_n + 1), in(_n + 1), out(_n + 1) {}
  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  void dfs(int u, int p = 0) {
    in[u] = ++timer;
    flat.push_back(u);
    for (int v : adj[u])
      if (v != p) dfs(v, u);
    out[u] = timer;
  }
  void build(int root = 1) { dfs(root); }
};
