// Diameter: farthest pair in convex polygon, returns actual distance
ld rotating_diameter(vector<P> &h) {
  int n = h.size();
  if (n <= 1) return 0;
  if (n == 2) return (h[0] - h[1]).abs();
  ld ans = 0;
  for (int i = 0, j = 1; i < n; i++) {
    while ((h[(i + 1) % n] - h[i]) * (h[(j + 1) % n] - h[j]) > 0) j = (j + 1) % n;
    ans = max({ans, (h[i] - h[j]).sq(), (h[(i + 1) % n] - h[j]).sq()});
  }
  return sqrtl(ans);
}
// Width: minimum distance between parallel supporting lines
ld polygon_width(vector<P> &h) {
  int n = h.size();
  if (n <= 2) return 0;
  ld ans = 1e30;
  for (int i = 0, j = 1; i < n; i++) {
    while ((h[(i + 1) % n] - h[i]) * (h[(j + 1) % n] - h[j]) > 0) j = (j + 1) % n;
    ld d = fabsl((h[(i + 1) % n] - h[i]) * (h[j] - h[i])) / (h[(i + 1) % n] - h[i]).abs();
    ans = min(ans, d);
  }
  return ans;
}
