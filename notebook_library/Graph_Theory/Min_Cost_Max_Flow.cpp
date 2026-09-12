struct MCMF {
  struct edge {
    int v, rev;
    ll cap, cost;
  };
  int N;
  vector<vector<edge>> g;
  vector<ll> dist, pi;
  vector<int> preve, prevv;
  const ll INF = 1LL << 62;
  MCMF(int n) : N(n), g(n), dist(n), pi(n), preve(n), prevv(n) {}
  void addEdge(int u, int v, ll cap, ll cost) {
    g[u].push_back({v, (int)g[v].size(), cap, cost});
    g[v].push_back({u, (int)g[u].size() - 1, 0, -cost});
  }
  ll maxflow(int s, int t) {
    if (s == t) return 0;
    ll flow = 0, cost = 0;
    fill(pi.begin(), pi.end(), INF);
    pi[s] = 0;
    for (int _ = 0; _ < N; _++) {
      bool any = false;
      for (int u = 0; u < N; u++)
        if (pi[u] != INF)
          for (auto& e : g[u])
            if (e.cap > 0 && pi[u] + e.cost < pi[e.v]) pi[e.v] = pi[u] + e.cost, any = true;
      if (!any) break;
    }
    // detect negative cycle: if any update still possible, potentials are broken
    for (int u = 0; u < N; u++)
      if (pi[u] != INF)
        for (auto& e : g[u])
          if (e.cap > 0 && pi[u] + e.cost < pi[e.v]) return cost;  // return 0 cost flow to avoid infinite loop
    while (true) {
      fill(dist.begin(), dist.end(), INF);
      dist[s] = 0;
      priority_queue<pair<ll, int>> pq;
      pq.push({0, s});
      while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (-d > dist[u]) continue;
        for (int i = 0; i < (int)g[u].size(); i++) {
          edge& e = g[u][i];
          ll nd = dist[u] + e.cost + pi[u] - pi[e.v];
          if (e.cap > 0 && nd < dist[e.v]) {
            dist[e.v] = nd;
            prevv[e.v] = u;
            preve[e.v] = i;
            pq.push({-nd, e.v});
          }
        }
      }
      if (dist[t] == INF) break;
      for (int i = 0; i < N; i++)
        if (dist[i] < INF) pi[i] += dist[i];
      ll f = INF;
      for (int u = t; u != s; u = prevv[u]) f = min(f, g[prevv[u]][preve[u]].cap);
      for (int u = t; u != s; u = prevv[u]) {
        edge& e = g[prevv[u]][preve[u]];
        e.cap -= f;
        g[e.v][e.rev].cap += f;
      }
      flow += f;
      cost += f * pi[t];
    }
    return cost;
  }
};
