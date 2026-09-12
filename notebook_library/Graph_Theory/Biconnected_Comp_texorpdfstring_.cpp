struct BCC {
  int n, timer, comps;
  vector<vector<int>> adj, tree;
  vector<int> tin, low, comp;
  vector<bool> is_bridge, vis;
  vector<pair<int, int>> edges;
  BCC(int _n) : n(_n), timer(0), comps(0), adj(_n), tin(_n, -1), low(_n, -1), comp(_n, -1), vis(_n, false) {}
  void add_edge(int u, int v) {
    adj[u].push_back(edges.size());
    adj[v].push_back(edges.size());
    edges.push_back({u, v});
    is_bridge.push_back(false);
  }
  void dfs(int u, int peid = -1) {
    vis[u] = true;
    tin[u] = low[u] = timer++;
    for (int id : adj[u]) {
      int v = edges[id].first ^ edges[id].second ^ u;
      if (id == peid) continue;
      if (vis[v]) low[u] = min(low[u], tin[v]);
      else {
        dfs(v, id);
        low[u] = min(low[u], low[v]);
        if (low[v] > tin[u]) is_bridge[id] = true;
      }
    }
  }
  void build_tree() {
    for (int i = 0; i < n; i++)
      if (!vis[i]) dfs(i);
    vector<int> q;
    for (int i = 0; i < n; i++) {
      if (comp[i] != -1) continue;
      q.push_back(i);
      comp[i] = comps++;
      while (!q.empty()) {
        int u = q.back();
        q.pop_back();
        for (int id : adj[u]) {
          int v = edges[id].first ^ edges[id].second ^ u;
          if (comp[v] == -1 && !is_bridge[id]) {
            comp[v] = comp[u];
            q.push_back(v);
          }
        }
      }
    }
    tree.resize(comps);
    for (int i = 0; i < (int)edges.size(); i++) {
      if (is_bridge[i]) {
        int u = comp[edges[i].first], v = comp[edges[i].second];
        tree[u].push_back(v);
        tree[v].push_back(u);
      }
    }
  }
};
