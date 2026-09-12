// sort queries: blocks of size B, snake-order within blocks (even/odd block sorting)
sort(cu.begin(), cu.end(), [&](auto &x, auto &y) {
  if (x.l / B != y.l / B) return x.l / B < y.l / B;
  return (x.l / B) % 2 ? x.r > y.r : x.r < y.r;
});
int R = -1, L = 0;       // [L,R] is current active window
while (R < r) add(++R);  // expand right first
while (L > l) add(--L);  // expand left
while (R > r) rem(R--);  // shrink right
while (L < l) rem(L++);  // shrink left
