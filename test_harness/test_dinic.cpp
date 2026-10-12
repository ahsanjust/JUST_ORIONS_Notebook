#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (1LL<<61);

// ===== NEW Dinic from notebook =====
struct DinicNew {
  struct edge { int to, rev; ll flow, w; };
  const ll inf = 1e18;
  int n, s, t;
  vector<vector<edge>> g;
  vector<int> lvl, ptr;
  vector<bool> in_s;
  vector<pair<int,int>> cut;
  DinicNew(int n, int s, int t) : n(n), s(s), t(t), 
    g(n), lvl(n), ptr(n), in_s(n) {}
  void add_edge(int u, int v, ll w, bool directed = false) {
    if (u == v) return;
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
    queue<int> q; q.push(s); in_s[s] = true;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (auto &e : g[u]) {
        int v = e.to;
        if (e.flow < e.w && !in_s[v])
          in_s[v] = true, q.push(v);
      }
    }
    cut.clear();
    for (int u = 0; u < n; u++)
      for (auto &e : g[u])
        if (in_s[u] && !in_s[e.to])
          cut.push_back({u, e.to});
    return f;
  }
};

// ===== OLD Dinic from notebook =====
struct DinicOld {
  struct Edge { int u, v; ll cap, flow; };
  const ll inf = 1e18;
  int n, s, t;
  vector<Edge> edges;
  vector<vector<int>> adj;
  vector<int> lvl, ptr, cut;
  vector<bool> in_s;
  DinicOld(int n, int s, int t) : n(n), s(s), t(t), 
    adj(n), lvl(n), ptr(n), in_s(n) {}
  void add_edge(int u, int v, ll cap) {
    adj[u].push_back(edges.size());
    edges.push_back({u, v, cap, 0});
    adj[v].push_back(edges.size());
    edges.push_back({v, u, 0, 0});
  }
  bool bfs() {
    fill(lvl.begin(), lvl.end(), -1);
    lvl[s] = 0; queue<int> q; q.push(s);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int id : adj[u]) {
        auto& e = edges[id];
        if (e.cap - e.flow > 0 && lvl[e.v] == -1) {
          lvl[e.v] = lvl[u] + 1; q.push(e.v);
        }
      }
    }
    return lvl[t] != -1;
  }
  ll dfs(int u, ll pushed) {
    if (pushed == 0 || u == t) return pushed;
    for (int &i=ptr[u]; i<(int)adj[u].size(); ++i) {
      int id = adj[u][i]; auto& e = edges[id];
      ll rem = e.cap - e.flow;
      if (lvl[u]+1 != lvl[e.v] || rem == 0) continue;
      ll tr = dfs(e.v, min(pushed, rem));
      if (tr == 0) continue;
      e.flow += tr; edges[id ^ 1].flow -= tr;
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
    queue<int> q; q.push(s); in_s[s] = true;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int id : adj[u]) {
        auto& e = edges[id];
        if (e.cap - e.flow > 0 && !in_s[e.v])
          in_s[e.v] = true, q.push(e.v);
      }
    }
    for (int i=0; i<(int)edges.size(); i+=2) 
      if (in_s[edges[i].u] && !in_s[edges[i].v]) 
        cut.push_back(i);
    return f;
  }
};

// ===== Reference: Edmonds-Karp (BFS augmenting) =====
struct EdmondsKarp {
  struct Edge { int to; ll cap, flow; };
  int n, s, t;
  vector<vector<Edge>> g;
  EdmondsKarp(int n, int s, int t) : n(n), s(s), t(t), g(n) {}
  void add_edge(int u, int v, ll w, bool directed = false) {
    if (u == v) return;
    g[u].push_back({v, w, 0});
    g[v].push_back({u, directed ? 0 : w, 0});
  }
  ll max_flow() {
    ll f = 0;
    while (true) {
      vector<int> p(n, -1);
      vector<ll> push(n, 0);
      queue<int> q; q.push(s); push[s] = INF;
      while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &e : g[u]) {
          if (e.cap - e.flow > 0 && p[e.to] == -1) {
            p[e.to] = u;
            push[e.to] = min(push[u], e.cap - e.flow);
            q.push(e.to);
            if (e.to == t) break;
          }
        }
      }
      if (p[t] == -1) break;
      ll tr = push[t]; f += tr;
      for (int v = t; v != s; v = p[v]) {
        for (auto &e : g[p[v]]) if (e.to == v) { e.flow += tr; break; }
        for (auto &e : g[v]) if (e.to == p[v]) { e.flow -= tr; break; }
      }
    }
    return f;
  }
};

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tests = 0, passed = 0;
  
  // Test 1: Simple known graphs
  {
    int n = 4, s = 0, t = 3;
    DinicNew dn(n, s, t); DinicOld dold(n, s, t); EdmondsKarp ek(n, s, t);
    dn.add_edge(0,1,1000); dn.add_edge(1,3,1000); dn.add_edge(0,2,1000); dn.add_edge(2,3,1000);
    dold.add_edge(0,1,1000); dold.add_edge(1,3,1000); dold.add_edge(0,2,1000); dold.add_edge(2,3,1000);
    ek.add_edge(0,1,1000); ek.add_edge(1,3,1000); ek.add_edge(0,2,1000); ek.add_edge(2,3,1000);
    ll rn = dn.max_flow(), ro = dold.max_flow(), re = ek.max_flow();
    if (rn == ro && ro == re) passed++; else cout << "FAIL test1: " << rn << " " << ro << " " << re << "\n";
    tests++;
  }
  
  // Test 2: Directed edge
  {
    int n = 3, s = 0, t = 2;
    DinicNew dn(n, s, t);
    dn.add_edge(0,1,5, true); dn.add_edge(1,2,3, true);
    ll r = dn.max_flow();
    if (r == 3) passed++; else cout << "FAIL test2: " << r << "\n";
    tests++;
  }
  
  // Test 3: Self-loop should be ignored
  {
    int n = 3, s = 0, t = 2;
    DinicNew dn(n, s, t); DinicOld dold(n, s, t);
    dn.add_edge(0,0,100); dn.add_edge(0,1,10); dn.add_edge(1,2,10);
    dold.add_edge(0,0,100); dold.add_edge(0,1,10); dold.add_edge(1,2,10);
    ll rn = dn.max_flow(), ro = dold.max_flow();
    if (rn == ro) passed++; else cout << "FAIL test3: " << rn << " " << ro << "\n";
    tests++;
  }
  
  // Test 4: Random graphs
  for (int iter = 0; iter < 1000; iter++) {
    int n = rng() % 8 + 2;
    int s = rng() % n;
    int t = rng() % n;
    if (s == t) t = (t+1)%n;
    int m = rng() % (n*n);
    DinicNew dn(n, s, t); DinicOld dold(n, s, t); EdmondsKarp ek(n, s, t);
    bool directed = rng()%2;
    for (int i = 0; i < m; i++) {
      int u = rng()%n, v = rng()%n;
      ll w = rng()%20 + 1;
      dn.add_edge(u,v,w,directed);
      dold.add_edge(u,v,w);
      ek.add_edge(u,v,w,directed);
    }
    ll rn = dn.max_flow(), ro = dold.max_flow(), re = ek.max_flow();
    if (rn == ro && ro == re) passed++;
    else {
      cout << "FAIL test4 iter=" << iter << ": new=" << rn << " old=" << ro << " ek=" << re << "\n";
      break;
    }
    tests++;
  }
  
  cout << "Passed " << passed << "/" << tests << " tests\n";
  return 0;
}
