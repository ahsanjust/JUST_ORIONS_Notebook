struct Dinic {
  struct edge { int to, rev; ll flow, w; };
  const ll inf = 1e18;
  int n, s, t;
  vector<vector<edge>> g;
  vector<int> lvl, ptr;
  vector<array<int,3>> edges;                 // {u, v, directed} of original edges
  Dinic(int n, int s, int t) : n(n), s(s), t(t), 
    g(n), lvl(n), ptr(n) {}
  void add_edge(int u, int v, ll w, bool directed = false) {
    if (u == v) return;
    edges.push_back({u, v, (int)directed});
    edge a = {v, (int)g[v].size(), 0, w};
    edge b = {u, (int)g[u].size(), 0, directed ? 0 : w};
    g[u].push_back(a), g[v].push_back(b);
  }
  bool bfs() {
    fill(lvl.begin(), lvl.end(), -1);
    lvl[s] = 0; queue<int> q; q.push(s);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (auto &e : g[u]) {
        int v = e.to;
        if (e.flow < e.w && lvl[v] == -1) {
          lvl[v] = lvl[u] + 1; q.push(v);
        }
      }
    }
    return lvl[t] != -1;
  }
  ll dfs(int u, ll pushed) {
    if (pushed == 0 || u == t) return pushed;
    for (int &i = ptr[u]; i < (int)g[u].size(); ++i) {
      edge &e = g[u][i];
      if (e.w <= e.flow) continue;
      int v = e.to;
      if (lvl[u]+1 != lvl[v]) continue;
      ll tr = dfs(v, min(pushed, e.w - e.flow));
      if (tr == 0) continue;
      e.flow += tr; g[v][e.rev].flow -= tr;
      return tr;
    }
    return 0;
  }
  ll max_flow() {
    ll f = 0, pushed;
    while (bfs()) {
      fill(ptr.begin(), ptr.end(), 0);
      while ((pushed = dfs(s, inf)) > 0) f += pushed;
    }
    return f;                   // the last (failed) bfs left lvl[] = source side of the cut
  }
  // Min-cut edges among nodes with both endpoints <= M (call right after max_flow()).
  // lvl[v] >= 0  <=>  v on the source side;  lvl[v] == -1  <=>  sink side.
  vector<pair<int,int>> min_cut(int M = INT_MAX) {
    vector<pair<int,int>> ans;
    for (auto &[u, v, dir] : edges) if (max(u, v) <= M) {
      bool ru = lvl[u] >= 0, rv = lvl[v] >= 0;
      if (dir ? (ru && !rv) : (ru != rv)) ans.push_back({u, v});
    }
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    return ans;
  }
};
