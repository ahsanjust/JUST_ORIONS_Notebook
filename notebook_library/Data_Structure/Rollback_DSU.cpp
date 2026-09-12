struct RollbackDSU {
  vector<int> e;
  vector<pair<int, int>> hist;
  RollbackDSU(int n) : e(n, -1) {}
  int find(int x) {
    while (e[x] >= 0) x = e[x];
    return x;
  }
  int size(int x) { return -e[find(x)]; }
  int time() { return hist.size(); }
  void rollback(int t) {
    while ((int)hist.size() > t) {
      auto [x, v] = hist.back();
      hist.pop_back();
      e[x] = v;
    }
  }
  bool unite(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    hist.push_back({a, e[a]});
    hist.push_back({b, e[b]});
    e[a] += e[b];
    e[b] = a;
    return true;
  }
};
