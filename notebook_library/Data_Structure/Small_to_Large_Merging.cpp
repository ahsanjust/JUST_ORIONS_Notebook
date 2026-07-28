// Example: DSU + vector per component (vector uses ~8x less memory than set)
vector<vector<int>> comp(n);
vector<int> par(n);
iota(par.begin(), par.end(), 0);
function<int(int)> find = [&](int x) {
  while (par[x] != x)
    x = par[x] = par[par[x]];
  return x;
};
auto unite = [&](int u, int v) {
  u = find(u), v = find(v);
  if (u == v)
    return;
  if (comp[u].size() < comp[v].size())
    swap(u, v);
  par[v] = u;
  comp[u].insert(comp[u].end(),
    comp[v].begin(), comp[v].end());
  comp[v].clear();
  // sort(comp[u].begin(), comp[u].end());
  // comp[u].erase(unique(...), comp[u].end());
};
