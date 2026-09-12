vector<string> lyndon(const string &s) {
  int n = s.size();
  vector<string> res;
  for (int i = 0; i < n;) {
    int j = i + 1, k = i;
    while (j < n && s[k] <= s[j]) {
      if (s[k] < s[j]) k = i;
      else k++;
      j++;
    }
    while (i <= k) {
      res.push_back(s.substr(i, j - k));
      i += j - k;
    }
  }
  return res;
}
