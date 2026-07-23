int64_t maxRectSum(vector<vector<int>>& a) {
  int n = a.size(), m = a[0].size();
  int64_t ans = -4e18;  // Safe negative infinity
  for (int top = 0; top < n; top++) {
    vector<int64_t> col(m, 0);
    for (int bot = top; bot < n; bot++) {
      for (int j = 0; j < m; j++)
        col[j] += a[bot][j];
      int64_t cur = 0;
      for (int j = 0; j < m; j++) {
        cur = max(col[j], cur + col[j]);
        ans = max(ans, cur);
      }
    }
  }
  return ans;
}
