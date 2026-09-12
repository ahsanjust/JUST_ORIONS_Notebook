vector<int> getPeriods(const vector<int> &pi) {
  if (pi.empty()) return {};
  int n = pi.size(), p = pi.back();
  vector<int> periods;
  while (p > 0) {
    periods.push_back(n - p);
    p = pi[p - 1];
  }
  return periods;
}
