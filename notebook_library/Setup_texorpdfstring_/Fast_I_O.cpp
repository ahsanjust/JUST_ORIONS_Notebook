inline char gc() {
  static char buf[1 << 16];
  static size_t bc, be;
  if (bc >= be) {
    buf[0] = 0, bc = 0;
    be = fread(buf, 1, sizeof(buf), stdin);
  }
  return buf[bc++];
}
int readInt() {
  int a, c;
  while ((a = gc()) < 40)
    if (a == 0)
      return 0;
  bool minus = (a == '-');
  if (minus)
    a = gc();
  unsigned res = a - 48;
  while ((c = gc()) >= 48)
    res = res * 10 + (c - 48);
  return minus ? -(long long)res : (int)res;
}
// ~5x faster than cin/scanf
