#include <bits/stdc++.h>
using namespace std;

// --- Bit & Mask Iteration ---
// 1. Iterate set bits of x:
// for (int s = x; s; s &= s - 1) { int i = __builtin_ctz(s); }
// 2. Iterate non-empty submasks of m:
// for (int s = m; s; s = (s - 1) & m) { }
// 3. Iterate supersets of mask m (< 2^n):
// for (int s = m; s < (1 << n); s = (s + 1) | m) { }

// --- Gray Code ---
int to_gray(int x) { return x ^ (x >> 1); }
int from_gray(int g) {
  for (int s = g >> 1; s; s >>= 1) g ^= s;
  return g;
}
