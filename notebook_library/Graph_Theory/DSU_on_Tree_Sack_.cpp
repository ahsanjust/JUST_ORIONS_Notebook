int timer = 0;
vector<int> sz, in, out, flat, big;
void dfs_sz(int u, int p) {
  sz[u] = 1, big[u] = 0, in[u] = ++timer, flat[timer] = u;
  for (int v : adj[u]) {
    if (v != p) {
      dfs_sz(v, u);
      sz[u] += sz[v];
      if (sz[v] > sz[big[u]])
        big[u] = v;
    }
  }
  out[u] = timer;
}
void add(int u, int val) { /* update DS */ }
void dfs_sack(int u, int p, bool keep) {
  for (int v : adj[u])
    if (v != p && v != big[u])
      dfs_sack(v, u, 0);
  if (big[u])
    dfs_sack(big[u], u, 1);
  for (int v : adj[u])
    if (v != p && v != big[u])
      for (int i = in[v]; i <= out[v]; i++)
        add(flat[i], 1);
  add(u, 1);
  // answer queries for subtree u here
  if (!keep)
    for (int i = in[u]; i <= out[u]; i++)
      add(flat[i], -1);
}
// Init: sz/in/out/flat/big.assign(n+1, 0);
// dfs_sz(1, 0); dfs_sack(1, 0, 1);
