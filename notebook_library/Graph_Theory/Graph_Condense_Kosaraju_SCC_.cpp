struct SCC {
  int n, comps;
  vector<vector<int>> adj, rev_adj, scc_adj;
  vector<int> order, comp;
  vector<bool> vis;
  SCC(int _n) : n(_n), comps(0), adj(_n), rev_adj(_n), comp(_n, -1), vis(_n, false) {}
  void add_edge(int u, int v) {
    adj[u].push_back(v);
    rev_adj[v].push_back(u);
  }
  void dfs1(int u) {
    vis[u] = true;
    for (int v : adj[u])
      if (!vis[v])
        dfs1(v);
    order.push_back(u);
  }
  void dfs2(int u, int id) {
    comp[u] = id;
    for (int v : rev_adj[u])
      if (comp[v] == -1)
        dfs2(v, id);
  }
  void build() {
    for (int i = 0; i < n; i++)
      if (!vis[i])
        dfs1(i);
    reverse(order.begin(), order.end());
    for (int u : order) {
      if (comp[u] == -1)
        dfs2(u, comps++);
    }
    scc_adj.resize(comps);
    for (int u = 0; u < n; u++) {
      for (int v : adj[u]) {
        if (comp[u] != comp[v])
          scc_adj[comp[u]].push_back(comp[v]);
      }
    }
  }
};
