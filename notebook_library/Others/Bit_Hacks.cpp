// --- Basic ops ---
x & -x                 // LSB value
            x&(x - 1)  // unset LSB
            x
        | (x - 1)   // set trailing 0s to 1
        ~x&(x + 1)  // isolate lowest 0-bit
        x
    && !(x & (x - 1))  // is power of two?
           x
           >> i& 1  // get bit i
           x
    |= (1 << i)  // set bit i
    x
    &= ~(1 << i)  // clear bit i
       x
    ^= (1 << i)  // toggle bit i
           (1 << k) -
           1  // mask of k lowest bits
           // --- GCC builtins (suffix ll for 64-bit; undef for 0) ---
           __builtin_popcount(x)  // # of 1-bits
           __builtin_clz(x)       // leading zeros
           __builtin_ctz(x)       // trailing zeros
           __builtin_parity(x)    // popcount mod 2
           // --- MSB / bit width (32-bit) ---
           31 -
           __builtin_clz(x)  // MSB position (0-idx)
           32 -
           __builtin_clz(x)  // bit width
           1
       << (31 - __builtin_clz(x))  // MSB value
       // --- Iterate set bits of x ---
       for (int s = x; s; s &= s - 1) {
  int i = __builtin_ctz(s);  // current bit index
}
// --- Iterate submasks of mask m ---
for (int s = m;; s = (s - 1) & m) {
  if (s == 0) break;
}
// --- Next number with same popcount ---
int next_popcount(int x) {
  int c = x & -x, r = x + c;
  return r | (((r ^ x) >> 2) / c);
}
// --- Round up to power of two ---
uint32_t next_pow2(uint32_t n) {
  n--;
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  n |= n >> 16;
  return ++n;
}
// 64-bit: add n |= n>>32
// --- Gray code ---
int gray = x ^ (x >> 1);  // binary -> Gray
// Gray -> binary: g = gray; for (int m = g>>1; m; m>>=1) g ^= m;
