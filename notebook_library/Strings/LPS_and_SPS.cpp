vector<int> getLps(const string &t) {
  int n = t.size();
  vector<int> pi(n, 0);
  int lps = 0;
  for (int q = 1; q < n; q++) {
    while (lps > 0 && t[lps] != t[q])
      lps = pi[lps - 1];
    if (t[lps] == t[q])
      lps += 1;
    pi[q] = lps;
  }
  return pi;
}
vector<int> getSps(const vector<int> &pi) {
  int n = pi.size();
  vector<int> sps(n, 0);
  for (int i = 1; i < n; i++) {
    if (pi[i] == 0)
      sps[i] = 0;
    else if (pi[pi[i] - 1] == 0)
      sps[i] = pi[i];
    else
      sps[i] = sps[pi[i] - 1];
  }
  return sps;
}
