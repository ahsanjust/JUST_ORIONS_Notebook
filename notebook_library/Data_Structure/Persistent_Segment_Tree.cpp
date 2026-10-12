// Value-domain PST (chairman tree) over compressed values [1..m].
// Define GLOBALLY (~46MB). Node 0 = null. O(log m) per op.
const int VN = 200000;
const int VM = VN * 20;
int vlc[VM], vrc[VM], vval[VM], vtot;
void vreset() { vtot = 0; vlc[0] = vrc[0] = vval[0] = 0; }
int vupd(int pre, int b, int e, int i, int v) {
  int cur = ++vtot;
  vlc[cur] = vlc[pre]; vrc[cur] = vrc[pre];
  if (b == e) { vval[cur] = vval[pre] + v; return cur; }
  int m = (b + e) >> 1;
  if (i <= m) vlc[cur] = vupd(vlc[pre], b, m, i, v);
  else        vrc[cur] = vupd(vrc[pre], m + 1, e, i, v);
  vval[cur] = vval[vlc[cur]] + vval[vrc[cur]];
  return cur;
}
// k-th smallest (compressed idx) in a[l..r], iterative.
int vkth(int pre, int cur, int b, int e, int k) {
  while (b < e) {
    int m = (b + e) >> 1;
    int left = vval[vlc[cur]] - vval[vlc[pre]];
    if (k <= left) { cur = vlc[cur]; pre = vlc[pre]; e = m; }
    else { cur = vrc[cur]; pre = vrc[pre]; b = m + 1; k -= left; }
  }
  return b;
}
// count of values <= x (compressed) in a[l..r].
int vcnt(int pre, int cur, int b, int e, int x) {
  if (x < b) return 0;
  int res = 0;
  while (b < e) {
    int m = (b + e) >> 1;
    if (x <= m) { cur = vlc[cur]; pre = vlc[pre]; e = m; }
    else { res += vval[vlc[cur]] - vval[vlc[pre]]; cur = vrc[cur]; pre = vrc[pre]; b = m + 1; }
  }
  return res + vval[cur] - vval[pre];
}
// k-th: vkth(vroot[l-1],vroot[r],1,m,k); map back via vals[idx].

// Position-domain PST over indices [1..n]. GLOBALLY (~92MB). Node 0 = null.
const int PN = 200000;
const int PM = PN * 40;
int plc[PM], prc[PM], pval[PM], ptot;
void preset() { ptot = 0; plc[0] = prc[0] = pval[0] = 0; }
int pupd(int pre, int b, int e, int i, int v) {
  int cur = ++ptot;
  plc[cur] = plc[pre]; prc[cur] = prc[pre];
  if (b == e) { pval[cur] = pval[pre] + v; return cur; }
  int m = (b + e) >> 1;
  if (i <= m) plc[cur] = pupd(plc[pre], b, m, i, v);
  else        prc[cur] = pupd(prc[pre], m + 1, e, i, v);
  pval[cur] = pval[plc[cur]] + pval[prc[cur]];
  return cur;
}
int pqry(int cur, int b, int e, int l, int r) {
  if (!cur || l > e || r < b) return 0;
  if (l <= b && e <= r) return pval[cur];
  int m = (b + e) >> 1;
  return pqry(plc[cur], b, m, l, r) + pqry(prc[cur], m + 1, e, l, r);
}
// Distinct [l,r]: unordered_map<int,int> last;
// r=proot[i-1]; if(last[a[i]])r=pupd(r,1,n,last[a[i]],-1);
// proot[i]=pupd(r,1,n,i,1); ans=pqry(proot[r],1,n,l,r).
// Distinct sum: use +-a[i] instead of +-1 (pval -> long long).
