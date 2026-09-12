const ll LINF = LLONG_MAX / 2;
struct Edge {
  int a, b;
  ll w;
};
struct BFNode {
  ll dist = LINF;
  int prev = -1;
};
void bellmanFord(vector<BFNode>& nodes, vector<Edge>& eds, int s) {
  nodes[s].dist = 0;
  int n = nodes.size();
  for (int i = 0; i < n; i++) {
    bool changed = false;
    for (Edge& e : eds) {
      if (nodes[e.a].dist == LINF) continue;
      ll d = nodes[e.a].dist + e.w;
      if (d < nodes[e.b].dist) {
        nodes[e.b].dist = (i < n - 1 ? d : -LINF);
        nodes[e.b].prev = e.a;
        changed = true;
      }
    }
    if (!changed) break;
  }
  for (int i = 0; i < n; i++)
    for (Edge& e : eds)
      if (nodes[e.a].dist == -LINF) nodes[e.b].dist = -LINF;
}
