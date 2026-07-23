vector<int> eulerPath(vector<vector<pair<int, int>>>& gr, int nedges, int src = 0) {
  int n = gr.size();
  vector<int> its(n), used(nedges), ret;
  vector<int> s = {src};
  while (!s.empty()) {
    int x = s.back(), &it = its[x];
    if (it == (int)gr[x].size()) {
      ret.push_back(x);
      s.pop_back();
    } else {
      auto [y, eid] = gr[x][it++];
      if (!used[eid]) {
        used[eid] = 1;
        s.push_back(y);
      }
    }
  }
  if ((int)ret.size() != nedges + 1)
    return {};
  reverse(ret.begin(), ret.end());
  return ret;
}
