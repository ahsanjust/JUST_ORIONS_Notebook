// Example: DSU + set per component
vector<set<int>> comp(n);
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
  for (int x : comp[v])
    comp[u].insert(x);
  comp[v].clear();
};
