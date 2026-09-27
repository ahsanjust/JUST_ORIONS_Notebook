string str_add(string a, string b) {
  if (a.size() < b.size()) swap(a, b);
  int c = 0, i = a.size() - 1, j = b.size() - 1;
  for (; i >= 0 || j >= 0 || c; c /= 10, i--) {
    c += (i >= 0 ? a[i] - '0' : 0) + (j >= 0 ? b[j--] - '0' : 0);
    if (i >= 0) a[i] = c % 10 + '0';
    else a.insert(0, 1, c % 10 + '0');
  }
  return a;
}
string str_sub(string a, string b) {
  if (a == "0" || a.empty()) return b;
  if (b == "0" || b.empty()) return a;
  int c = 0, i = a.size() - 1, j = b.size() - 1;
  for (; i >= 0; i--, c = c < 0) {
    int d = a[i] - '0' - c - (j >= 0 ? b[j--] - '0' : 0);
    a[i] = (d < 0 ? d + 10 : d) + '0';
  }
  size_t p = a.find_first_not_of('0');
  return p == string::npos ? "0" : a.substr(p);
}
string str_mul(string a, string b) {
  if (a == "0" || b == "0") return "0";
  if (a == "1") return b;
  if (b == "1") return a;
  if (a.size() < b.size()) swap(a, b);
  string r(a.size() + b.size(), '0');
  for (int i = a.size() - 1; i >= 0; i--) {
    int c = 0, x = a[i] - '0';
    for (int j = b.size() - 1; j >= 0; j--) {
      int s = x * (b[j] - '0') + (r[i + j + 1] - '0') + c;
      c = s / 10;
      r[i + j + 1] = s % 10 + '0';
    }
    r[i] += c;
  }
  size_t p = r.find_first_not_of('0');
  return p == string::npos ? "0" : r.substr(p);
}
