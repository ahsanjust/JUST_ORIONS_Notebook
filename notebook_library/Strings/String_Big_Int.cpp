// Signed decimal strings: optional '-', empty = 0, never returns "-0".
pair<bool, string> sparts(string s) {  // {neg, magnitude w/o leading zeros}
  bool neg = false;
  while (!s.empty() && (s[0] == '-' || s[0] == '+')) { neg ^= s[0] == '-'; s = s.substr(1); }
  size_t p = s.find_first_not_of('0');
  return {neg && p != string::npos, p == string::npos ? "0" : s.substr(p)};
}
int scmp(const string &a, const string &b) {  // magnitudes: -1,0,1
  return a.size() != b.size() ? (a.size() < b.size() ? -1 : 1) : a == b ? 0 : (a < b ? -1 : 1);
}
string uadd(string a, string b) {  // magnitudes
  if (a.size() < b.size()) swap(a, b);
  int c = 0, i = a.size() - 1, j = b.size() - 1;
  for (; i >= 0 || j >= 0 || c; c /= 10, i--) {
    c += (i >= 0 ? a[i] - '0' : 0) + (j >= 0 ? b[j--] - '0' : 0);
    if (i >= 0) a[i] = c % 10 + '0';
    else a.insert(0, 1, c % 10 + '0');
  }
  return a;
}
string usub(string a, string b) {  // magnitudes, requires a >= b
  int c = 0, i = a.size() - 1, j = b.size() - 1;
  for (; i >= 0; i--) {
    int d = a[i] - '0' - c - (j >= 0 ? b[j--] - '0' : 0);
    c = d < 0;
    a[i] = (d < 0 ? d + 10 : d) + '0';
  }
  size_t p = a.find_first_not_of('0');
  return p == string::npos ? "0" : a.substr(p);
}
string str_add(string a, string b) {
  auto [na, ma] = sparts(a);
  auto [nb, mb] = sparts(b);
  if (na == nb) {
    string m = uadd(ma, mb);
    return na && m != "0" ? "-" + m : m;
  }
  int c = scmp(ma, mb);
  if (c == 0) return "0";
  string m = c > 0 ? usub(ma, mb) : usub(mb, ma);
  return (c > 0 ? na : nb) ? "-" + m : m;
}
string str_sub(string a, string b) {
  if (!b.empty() && b[0] == '-') return str_add(a, b.substr(1));
  return str_add(a, "-" + b);
}
string str_mul(string a, string b) {
  auto [na, ma] = sparts(a);
  auto [nb, mb] = sparts(b);
  if (ma.size() < mb.size()) swap(ma, mb);
  string r(ma.size() + mb.size(), '0');
  for (int i = ma.size() - 1; i >= 0; i--) {
    int c = 0, x = ma[i] - '0';
    for (int j = mb.size() - 1; j >= 0; j--) {
      int s = x * (mb[j] - '0') + (r[i + j + 1] - '0') + c;
      c = s / 10;
      r[i + j + 1] = s % 10 + '0';
    }
    r[i] += c;
  }
  size_t p = r.find_first_not_of('0');
  string m = p == string::npos ? "0" : r.substr(p);
  return m == "0" || na == nb ? m : "-" + m;
}
