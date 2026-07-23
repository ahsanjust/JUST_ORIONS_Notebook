struct MergeSortTree {
  int n;
  vector<vector<int>> tree;
  MergeSortTree(const vector<int>& arr) {
    n = arr.size();
    tree.resize(4 * n);
    build(1, 0, n - 1, arr);
  }
  void build(int node, int l, int r, const vector<int>& arr) {
    if (l == r) {
      tree[node].push_back(arr[l]);
      return;
    }
    int mid = (l + r) / 2;
    build(2 * node, l, mid, arr);
    build(2 * node + 1, mid + 1, r, arr);
    merge(tree[2 * node].begin(), tree[2 * node].end(), tree[2 * node + 1].begin(), tree[2 * node + 1].end(),
          back_inserter(tree[node]));
  }
  int query(int node, int l, int r, int ql, int qr, int k) {
    if (l > qr || r < ql)
      return 0;
    if (l >= ql && r <= qr) {
      // binary search in sorted node list: count <= k
      return upper_bound(tree[node].begin(), tree[node].end(), k) - tree[node].begin();
    }
    int mid = (l + r) / 2;
    return query(2 * node, l, mid, ql, qr, k) + query(2 * node + 1, mid + 1, r, ql, qr, k);
  }
};
