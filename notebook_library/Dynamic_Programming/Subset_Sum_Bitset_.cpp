const int N = 1e6 + 6;
bitset<N> dp;
dp.set(0);
for (auto &[w, c] : comp) {
  for (int i = 0; (1LL << i) <= c; ++i) {
    dp |= dp << (w * (1LL << i));
    c -= 1LL << i;
  }
  dp |= dp << (w * c);
}
dp.test(k)  // if sum k is possible
