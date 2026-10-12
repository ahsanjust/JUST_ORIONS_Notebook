#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// Gauss-Jordan Elimination over GF(2) / F2 (Binary Field / XOR Linear System)
// ============================================================================
// Solves: A * x = b (mod 2)
//
// Key Features:
// 1. Bit-parallel: Row addition is O(1) via XOR (uint64_t for M <= 64).
// 2. RREF: Isolates pivot variables so each dependent variable depends only
//    on free variables.
// 3. Min-Weight Solution (e.g. Lights Out / Grid Toggle / Min Touches):
//    Iterates over all 2^k configurations of free variables in O(2^k * M).
//    Uses __builtin_parityll(A[row] & x) for instant O(1) evaluation per pivot.
//
// Parameters:
//   n : number of equations (rows)
//   m : number of variables (cols, m <= 64)
//   A : vector<uint64_t> of size n (A[i] is bitmask of coefficients of eq i)
//   b : vector<int> of size n (b[i] in {0, 1} is RHS target of eq i)
//   find_min : if true and free variables k <= 20, finds minimum popcount of x
//
// Returns:
//   Pair {min_weight, solution_mask}:
//   - min_weight = minimum popcount of x (minimum 1s/touches required)
//   - If system is inconsistent (no solution), returns {-1, 0}.
//   - solution_mask = bitmask of 0/1 assignments to variables (x_0 ... x_{m-1})
// ============================================================================

pair<int, uint64_t> gauss_gf2(int n, int m, vector<uint64_t> A, vector<int> b, bool find_min = true) {
  vector<int> piv_row(m, -1);
  int r = 0;

  // 1. Gauss-Jordan Elimination to RREF
  for (int c = 0; c < m && r < n; c++) {
    int sel = -1;
    for (int i = r; i < n; i++) {
      if (A[i] >> c & 1) {
        sel = i;
        break;
      }
    }
    if (sel == -1) continue;

    swap(A[r], A[sel]);
    swap(b[r], b[sel]);
    piv_row[c] = r;

    for (int i = 0; i < n; i++) {
      if (i != r && (A[i] >> c & 1)) {
        A[i] ^= A[r];
        b[i] ^= b[r];
      }
    }
    r++;
  }

  // 2. Consistency check: 0 * x = 1 is impossible
  for (int i = 0; i < n; i++) {
    if (A[i] == 0 && b[i] == 1) return {-1, 0ULL};
  }

  // 3. Identify Free Variables
  vector<int> free_vars;
  for (int c = 0; c < m; c++) {
    if (piv_row[c] == -1) free_vars.push_back(c);
  }

  int k = free_vars.size();

  // If min weight is not requested or k is too large for 2^k brute force:
  if (!find_min || k > 20) {
    uint64_t x = 0;
    for (int c = 0; c < m; c++) {
      if (piv_row[c] != -1 && b[piv_row[c]]) x |= (1ULL << c);
    }
    return {(int)__builtin_popcountll(x), x};
  }

  // 4. Min-weight search over all 2^k free variable combinations
  int best_weight = 1e9;
  uint64_t best_x = 0;

  for (int mask = 0; mask < (1 << k); mask++) {
    uint64_t x = 0;
    // Assign values to Free Variables according to mask
    for (int i = 0; i < k; i++) {
      if (mask >> i & 1) x |= (1ULL << free_vars[i]);
    }

    // Directly evaluate Pivot Variables from RREF in O(1)
    // In RREF, A[row] only has 1s at pivot column c and free variable columns.
    // Since bit c is not set in x yet, (A[row] & x) isolates the free variables!
    for (int c = 0; c < m; c++) {
      if (piv_row[c] != -1) {
        int row = piv_row[c];
        int sum_free = __builtin_parityll(A[row] & x);
        if (b[row] ^ sum_free) x |= (1ULL << c);
      }
    }

    int cur_weight = __builtin_popcountll(x);
    if (cur_weight < best_weight) {
      best_weight = cur_weight;
      best_x = x;
    }
  }

  return {best_weight, best_x};
}
