int64_t xor_0ton(int64_t n) {
  int r = n % 4;
  return r == 0 ? n : r == 1 ? 1 : r == 2 ? n + 1 : 0;
}
int64_t range_xor(int64_t l, int64_t r) {
  return xor_0ton(r) ^ xor_0ton(l - 1);
}
int64_t range_and(int64_t l, int64_t r) {
  int b = 0; while ((l >> b) ^ (r >> b)) b++;
  return (l >> b) << b;
}
int64_t range_or(int64_t l, int64_t r) {
  int b = 0; while ((l >> b) ^ (r >> b)) b++;
  return r | ((1LL << b) - 1);
}
