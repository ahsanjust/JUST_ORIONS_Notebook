struct Articulation {
  int n, timer, ecnt;
  vector<vector<pair<int,int>>> g;
  vector<int> tin, low;
  vector<bool> is_art, is_bridge;
  vector<pair<int,int>> bridges;
  Articulation(int _n, int _m) : n(_n), timer(0),
    ecnt(0), g(_n), tin(_n, -1), low(_n, -1),
    is_art(_n, false), is_bridge(_m, false) {}
  void add_edge(int u, int v) {
    g[u].push_back({v, ecnt});
    g[v].push_back({u, ecnt++});
  }
  void dfs(int u, int peid = -1) {
    tin[u] = low[u] = timer++;
    int children = 0;
    for (auto [v, eid] : g[u]) {
      if (eid == peid) continue;
      if (tin[v] != -1) {
        low[u] = min(low[u], tin[v]);
      } else {
        children++;
        dfs(v, eid);
        low[u] = min(low[u], low[v]);
        if (low[v] >= tin[u] && peid != -1)
          is_art[u] = true;
        if (low[v] > tin[u]) {
          bridges.push_back({min(u,v), max(u,v)});
          is_bridge[eid] = true;
        }
      }
    }
    if (peid == -1 && children > 1) is_art[u] = true;
  }
  void build() {
    for (int i = 0; i < n; i++)
      if (tin[i] == -1) dfs(i);
  }
};
