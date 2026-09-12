// DP template (bool[] avoids set overhead)
int g[N];
g[0] = 0;
for (int i = 1; i <= maxN; i++) {
  bool seen[K] = {};
  for (int m : moves)
    if (i >= m) seen[g[i - m]] = 1;
  int m = 0;
  while (seen[m]) m++;
  g[i] = m;
}
// Standard Nim: g(n) = n (XOR pile sizes / 1st wins if != 0)
// Subtraction {1..m}: g(n) = n % (m+1)
// Take & Break: g(n) = mex{ g(a) ^ g(b) | a+b=n }
// Staircase Nim: XOR odd-indexed piles only
// Wythoff: losing pairs = (floor(phi*k), floor(phi^2*k))
// Pattern: DP 100 terms for periodicity.
// g >> 1000 => closed form.
// Watch: mex includes 0; g(0)=0; add moves irrelevant;
// count losing via pairs XOR=0
