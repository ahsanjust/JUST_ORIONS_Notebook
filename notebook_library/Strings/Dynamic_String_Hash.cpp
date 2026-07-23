const int MOD[] = {127657753, 987654319}, BASE[] = {137, 277};
int pw[2][N], ipw[2][N];
int mpow(int a, int n, int m) {
  int r = 1;
  while (n) {
    if (n & 1)
      r = 1LL * r * a % m;
    a = 1LL * a * a % m;
    n >>= 1;
  }
  return r;
}
void init_hash(int n) {
  for (int k = 0; k < 2; k++) {
    pw[k][0] = ipw[k][0] = 1;
    for (int i = 1; i <= n; i++)
      pw[k][i] = 1LL * pw[k][i - 1] * BASE[k] % MOD[k];
    int inv = mpow(BASE[k], MOD[k] - 2, MOD[k]);
    for (int i = 1; i <= n; i++)
      ipw[k][i] = 1LL * ipw[k][i - 1] * inv % MOD[k];
  }
}
using H = array<int, 2>;
H add(H a, H b) {
  return {(a[0] + b[0]) % MOD[0], (a[1] + b[1]) % MOD[1]};
}
H mul(H a, H b) {
  return {(int)(1LL * a[0] * b[0] % MOD[0]), (int)(1LL * a[1] * b[1] % MOD[1])};
}
struct SegHash {
  int n;
  vector<H> fwd, rev;
  SegHash(string s) {
    n = s.size();
    s = "." + s;
    fwd.resize(4 * n);
    rev.resize(4 * n);
    build(1, 1, n, s);
  }
  void build(int node, int l, int r, string& s) {
    if (l == r) {
      fwd[node] = {(int)(1LL * s[l] * pw[0][l] % MOD[0]), (int)(1LL * s[l] * pw[1][l] % MOD[1])};
      rev[node] = {(int)(1LL * s[l] * pw[0][n - l + 1] % MOD[0]), (int)(1LL * s[l] * pw[1][n - l + 1] % MOD[1])};
      return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid, s);
    build(node * 2 + 1, mid + 1, r, s);
    fwd[node] = add(fwd[node * 2], fwd[node * 2 + 1]);
    rev[node] = add(rev[node * 2], rev[node * 2 + 1]);
  }
  void upd(int i, char c) {
    upd(1, 1, n, i, c);
  }
  void upd(int node, int l, int r, int idx, char c) {
    if (l == r) {
      fwd[node] = {(int)(1LL * c * pw[0][l] % MOD[0]), (int)(1LL * c * pw[1][l] % MOD[1])};
      rev[node] = {(int)(1LL * c * pw[0][n - l + 1] % MOD[0]), (int)(1LL * c * pw[1][n - l + 1] % MOD[1])};
      return;
    }
    int mid = (l + r) / 2;
    if (idx <= mid)
      upd(node * 2, l, mid, idx, c);
    else
      upd(node * 2 + 1, mid + 1, r, idx, c);
    fwd[node] = add(fwd[node * 2], fwd[node * 2 + 1]);
    rev[node] = add(rev[node * 2], rev[node * 2 + 1]);
  }
  H qry(vector<H>& t, int node, int l, int r, int i, int j) {
    if (i > r || j < l)
      return {0, 0};
    if (i <= l && r <= j)
      return t[node];
    int mid = (l + r) / 2;
    return add(qry(t, node * 2, l, mid, i, j), qry(t, node * 2 + 1, mid + 1, r, i, j));
  }
  H get_hash(int l, int r) {
    H h = qry(fwd, 1, 1, n, l, r);
    return mul(h, {ipw[0][l - 1], ipw[1][l - 1]});
  }
  H get_rev(int l, int r) {
    H h = qry(rev, 1, 1, n, l, r);
    return mul(h, {ipw[0][n - r], ipw[1][n - r]});
  }
  bool is_pal(int l, int r) {
    return get_hash(l, r) == get_rev(l, r);
  }
};
