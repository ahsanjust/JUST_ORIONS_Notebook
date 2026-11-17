// Tree Counting & Enumeration
// Formulas:
// 1. Labeled Unrooted: n^(n-2) (Cayley's formula)
// 2. Labeled Rooted: n * n^(n-2) = n^(n-1)
// 3. Labeled with degree seq (sum d_i = 2n-2, d_i >= 1): (n-2)! / prod (d_i - 1)!
// 4. Labeled Forest of k trees rooted at r_1..r_k: k * n^(n-k-1)
// 5. Spanning trees on K_{a,b}: a^(b-1) * b^(a-1)
// 6. Spanning trees on K_{n1..nk} (n = sum n_i): n^(k-2) * prod (n - n_i)^(n_i - 1)
// 7. General graph: Any cofactor of Laplacian L = D - A (Kirchhoff's Matrix Tree)
// 8. Unlabeled Binary Trees (n nodes): C_n = 1/(n+1) * binom(2n, n)
// 9. Labeled Binary Trees: n! * C_n = (2n)! / (n+1)!
// 10. Unlabeled Plane Rooted (n nodes): C_{n-1} = 1/n * binom(2n-2, n-1)
// 11. Labeled Plane Rooted: n! * C_{n-1} = (2n-2)! / (n-1)!

// Unlabeled Trees via Polya recurrence & Otter's formula:
// r[n] = unlabeled rooted trees (A000081): 1, 1, 2, 4, 9, 20, 48, 115, 286, 719...
// t[n] = unlabeled unrooted trees (A000055): 1, 1, 1, 2, 3, 6, 11, 23, 47, 106...
pair<vector<ll>, vector<ll>> count_unlabeled_trees(int max_n) {
  vector<ll> r(max_n + 1, 0), t(max_n + 1, 0);
  r[1] = t[1] = 1;
  for (int n = 2; n <= max_n; n++) {
    ll sum_all = 0;
    for (int i = 1; i < n; i++) {
      ll d_sum = 0;
      for (int d = 1; d <= i; d++) {
        if (i % d == 0) d_sum += d * r[d];
      }
      sum_all += d_sum * r[n - i];
    }
    r[n] = sum_all / (n - 1);

    ll sub = 0;
    for (int i = 1; i <= (n - 1) / 2; i++) sub += r[i] * r[n - i];
    if (n % 2 == 0) {
      ll mid = r[n / 2];
      sub += mid * (mid - 1) / 2;
    }
    t[n] = r[n] - sub;
  }
  return {r, t};
}
