# Stress-Test Guidelines for Agents

> **Target:** the C++ code inside `\begin{minted}{c++} ... \end{minted}` blocks in
> `notebook/sections/0[1-9]_*.tex` (the printed notebook snippets).
> This does **not** cover the standalone files in `library/`.
>
> **Goal:** catch compile errors, undefined behavior, logic bugs, and edge-case
> failures in a snippet *before* the PDF is printed.
>
> **Golden Rule: DOCUMENT ONLY. NEVER MODIFY NOTEBOOK SOURCE.**
> All findings are filed in `notebook/issues.md`. Fixes are a separate, approved step.
>
> **Tracker:** `docs/STRESSTEST_LOG.md` lists every section file and subsection that
> has been stress tested, with date, variants, and result. **Check it first** to
> avoid duplicating work. Append a row when you finish testing a file.

---

## 1. Scope & Sources

- Notebook snippets live in 10 section files:
  `notebook/sections/01_setup_and_basics.tex` … `10_others.tex`.
- Every `\begin{minted}{c++} … \end{minted}` block is tested — **no skipping**.
  ≈ 75–85 C++ blocks total. Some files also have `json`/formula blocks — skip those.
- A snippet is usually **just a struct/class with no `main`** (e.g. a `Trie`,
  `Sparse2D`, `dseg`). Some subsections are pure formulas or config — skip them.
- **Subsections already marked FIXED in `issues.md` are re-tested too.**
  Past fixes may reintroduce bugs or have incomplete patches.

### Common macros (NOT issues)
The notebook assumes the user defines these common CP macros in their own
template preamble. Missing them is **not** a notebook bug:
- `#define sz(x) (int)(x).size()` — used in matrix multiply and other snippets.
- `using ll = long long;` (or `typedef long long ll;`) — used pervasively.
- `#define all(x) (x).begin(), (x).end()`, `#define rall(x) (x).rbegin(), (x).rend()`
- Any other obvious brevity macros (e.g. `#define pb push_back`).
- `modpow` / `mod` — expected to be user-defined or taken from another snippet.
When testing, provide these definitions in the harness without filing an issue.

### Companion docs (match their conventions when reporting)
- `notebook/issues.md` — severity table: 🔴 Critical / 🟠 High / 🟡 Medium.
  File every confirmed bug here with file + line range + minimal repro.
- `analysis/*.md` — legend: 🐛 BUG / 🔧 QUALITY / ✨ POLISH.

---

## 2. Step 1 — Select a target

1. Pick **one subsection** (`\subsection{…}`) to test.
2. One subsection ≈ one snippet, or one tightly-coupled set (e.g. a struct and
   all its methods). Test it in isolation.
3. Skip non-C++ blocks (`json`) and pure-formula subsections.

---

## 3. Step 2 — Extract the snippet

1. Copy the code **between** `\begin{minted}{c++}` and `\end{minted}` into a
   standalone file under `/tmp/` (e.g. `/tmp/stress_<name>.cpp`).
   **Never edit the notebook source during testing.**
2. If the snippet is a bare struct/class with no `main`:
   - add `#include <bits/stdc++.h>` and `using namespace std;`
   - wrap it in an `int main() { … }` driver that exercises the operations.
3. If the snippet references helpers defined in *another* subsection
   (e.g. a `Point` struct, a `Mint` type), copy those in too — keep the test
   self-contained.

---

## 4. Step 3 — Build a brute-force oracle + property tests

For every query/operation the snippet exposes, write a trivial reference over the
same inputs:

- **Brute force:** O(N) / O(N²) / O(N³) reference that computes the same answer
  naively (e.g. `max` over a range, `count` via `std::count`, enumerate all
  subsets).
- **Property to check:** a precise equivalence, e.g.
  `trie.count_special(x) == count of y with y ≤ (x⊕y) ≤ x`.
- **Cover ALL of these dimensions (mandatory):**
  - *Correctness vs oracle* on random inputs (2000+ cases).
  - *Boundary values:* 0, 1, `INT_MAX`/`LLONG_MAX`, `INT_MIN`/`LLONG_MIN`,
    max allowed by snippet's own dimensions, duplicates, empty structure,
    single element, all elements identical.
  - *Round-trip / idempotence:* `add(x)` then `add(x, -1)` → structure empty;
    `add` then `undo` → state restored; `reverse` twice → identity.
  - *Invariant checks:* size counts match, parent pointers valid, tree is
    balanced, no cycles, sum of subtree counts == total count.
  - *Null / empty states:* empty container, zero-size input, all-zeros array,
    string of length 1, N = 0 or N = 1.
  - *Monotonicity / ordering:* queries return non-decreasing results for
    increasing parameters where the property holds.

---

## 5. Step 4 — Drive with randomized stress

1. Use a **seeded** RNG (`std::mt19937` or `std::mt19937_64`) for reproducibility.
2. Loop **2000–5000** randomized test cases (never fewer than 2000).
3. Per case: generate small random inputs, apply a random sequence of operations,
   and compare snippet output to the oracle.
4. On the **first mismatch**: print the inputs and **both** outputs, then `return 1`
   / `assert`. Do **not** swallow or skip failures.
5. Keep input sizes small (so the brute force stays fast) but exercise many cases.
6. **Test under adversarial patterns:** strictly increasing/decreasing inputs,
   all same value, alternating values, large then small, small then large.

---

## 6. Step 5 — Compile & configuration variants (critical)

Run **all** of the following:

1. **Normal build** (match the notebook's standard):
   `g++ -std=c++17 -O2 -o /tmp/t /tmp/stress_<name>.cpp`
2. **Sanitizers** (catch UB / overflow / OOB):
   `g++ -std=c++17 -O0 -fsanitize=address,undefined -o /tmp/t_san /tmp/stress_<name>.cpp`
   and run the harness under it.
3. **Contest `int = long long` variant** — *always run this*:
   wrap the extracted struct in `#define int long long` (or `using int = long long`)
   and re-run the full harness. For the struct only — `#undef int` around `main`.
   This surfaces:
   - `__builtin_clz` truncation / wrong-log on 64-bit values,
   - `vector::assign` with a negative (wrapped) size,
   - any 32-bit-only assumption,
   - `1 << i` overflow when `i >= 31`.

Check for: compile failures, segfaults, ASan/UBSan errors, wrong answers — under
**both** the plain build and the `int = long long` build.

---

## 7. Step 6 — Known failure patterns to watch for

From prior notebook audits and the `issues.md` tracker. If you see these, they are
very likely bugs:

- `vector::assign(n - k + 1, …)` where `k > n` → negative size → crash
  (`std::length_error`). *(Seen: 2D Sparse Table on small grids.)*
- Fixed-size arrays `st[10][10]` accessed at index `lg[1024] == 10` → out of bounds.
- Root / index-0 treated as "null": `if (!u) return 0;` kills a **valid** node 0.
  *(Seen: Binary Trie `count_special`.)*
- Missing child-existence guard before recursion: always `if (nxt[u][d])` before
  descending.
- `__builtin_clz(x)` / `__builtin_ctz(x)` called with `x ≤ 0` (UB), or relying on
  32-bit behavior under `int = long long`.
- Off-by-one in query ranges: `r - (1 << j) + 1` must stay ≥ the left bound.
- Wrong template depth, e.g. `vector<vector<vector<int>>>` where a
  `vector<vector<int>>` is intended → won't even compile.
- Signed integer overflow in `k + 1`, `mid = (l + r) / 2`, or `a * b % MOD`.
- `(ull)a * a % mod` overflows 64-bit when `a > 4e9` — needs `__uint128_t`.
- `int` overflow in `1 << i` when `i >= 31` — use `1LL << i` or `(T)1 << i`.
- `memset(dp, -1, sizeof(dp))` on `vector<>` instead of raw array → UB.
- Missing `assert(p >= 0)` in exponentiation — negative exponent silently returns
  identity matrix (do-nothing loop).
- `(k - i)` can be negative before modulo — must do `((k - i) % MOD + MOD) % MOD`.
- `n + 1` loop bound on array of size `n` → buffer over-read.
- Negative remainder in C++: `(a - b) % MOD` gives negative value — must use
  `(a - b + MOD) % MOD`.
- `size_t` narrowing on 32-bit platforms when casting `uint64_t` to `size_t`.

---

## 8. Severity definitions

| Severity | Meaning |
|----------|---------|
| 🔴 **Critical** | Compile error, crash (segfault/ABRT), or wrong answer on valid contest input. Will 100% cause a WA/RE in contest. Must fix before next contest. |
| 🟠 **High** | Fails on edge cases (large values, boundary conditions, unusual inputs, duplicates, empty state). Likely to trigger in a contest under time pressure. |
| 🟡 **Medium** | Minor issue: style violation, dead code, unused variable, potential performance problem, or a misuse that is unlikely but possible. Fix when time permits. |

---

## 9. Step 7 — Report & file (DOCUMENT ONLY)

If a bug is found:

1. Record it in `notebook/issues.md`:
   - section file, line range,
   - severity (🔴 Critical / 🟠 High / 🟡 Medium),
   - minimal reproducing inputs (code + data),
   - expected vs actual output,
   - root cause analysis (2–3 sentences).
2. **Do NOT edit the notebook during the audit.** No exception.
3. Propose the corrected snippet ONLY in the issue entry for reviewer approval.
4. After the full audit is complete, approved fixes are applied in a separate pass.

---

## Quick checklist

- [ ] Target subsection selected (one at a time)
- [ ] Snippet extracted to `/tmp/`, self-contained, with `main` driver
- [ ] Brute-force oracle + ALL boundary dimensions covered
- [ ] 2000–5000 randomized cases, first failure printed & stops
- [ ] Compiled: `-O2`, and `-fsanitize=address,undefined`
- [ ] Re-run under `#define int long long`
- [ ] Findings filed in `notebook/issues.md` (no direct edits yet)
