# Data Structure Optimization Analysis

> **Notebook:** JUST_ORIONS Team Reference (Section 5 — Data Structure)
> **Goal:** 25-page ICPC notebook, 3-column landscape, C++17, syntactically dense
> **Analysis scope:** Time & memory/space optimization opportunities for each data structure
> **Verification status:** Each claim verified against reference libraries (KACTL, maspypy) and/or web research
> **Caveat:** Notebook has ~4 pages of budget remaining — any changes must be weighed against page cost

> **⚠️ CRITICAL — Read Before Making Any Changes**
>
> This notebook is used in **live ICPC competitions**. Any mistake — a typo, a wrong variable, an off-by-one, a memory leak — can cost the team a solved problem and a medal. You MUST be flawless.
>
> **Rules for the agent:**
> 1. **Read the full file first** — understand the surrounding context before editing. Never edit blindly.
> 2. **One change at a time** — do not batch multiple modifications into one edit. Each change must be independently verified.
> 3. **After each modification**, run ALL three verifications before moving on:
>    - `make build` — confirm LaTeX compiles cleanly (no syntax errors in minted blocks)
>    - Compile the modified snippet with AddressSanitizer + UBSan:
>      `g++ -std=c++17 -O2 -fsanitize=address,undefined -o /tmp/test /tmp/test.cpp && /tmp/test`
>    - Run a random-input stress test against a brute-force reference to confirm correctness
> 4. **Update notes/comments in the subsection you modified** — if your change makes an existing comment incorrect, stale, or misleading, fix it. Any comment that says something is O(X) when the new code is O(Y), or describes a variable/strategy you changed, must be updated to match.
> 5. **Update the plan (this document) after every change** — mark the completed item as **`[DONE]`** in the priority table, update any status/verdict that is now stale, and clean up anything that no longer applies. Keep the document organized and tidy — this is the team's source of truth during development.
> 6. **Do NOT skip any verification**, even for "trivial" changes. The bug that hurts the team will be the one you thought was too small to test.
> 7. **If verification fails**, roll back the change and understand why before retrying. Do not "patch around" a failing test.
> 8. **Preserve the original notebook backup** before starting: `cp notebook/sections/05_data_structure.tex notebook/sections/05_data_structure.tex.bak`
>
> This is not optional. Your discipline determines whether this code helps or hurts the team at contest time.

---

## Table of Contents

1. [PBDS (Policy-Based Data Structure)](#1-pbds)
2. [GP Hash Table](#2-gp-hash-table)
3. [Rope (GNU)](#3-rope-gnu)
4. [DSU (Disjoint Set Union)](#4-dsu)
5. [Sparse Table](#5-sparse-table)
6. [Sparse Table 2D](#6-sparse-table-2d)
7. [Fenwick Tree (BIT)](#7-fenwick-tree)
8. [Fenwick 2D](#8-fenwick-2d)
9. [BIT Range Update & Range Query](#9-bit-range-update--range-query)
10. [Lazy Segment Tree](#10-lazy-segment-tree)
11. [Persistent Segment Tree](#11-persistent-segment-tree)
12. [Merge Sort Tree](#12-merge-sort-tree)
13. [Wavelet Tree](#13-wavelet-tree)
14. [Trie (Binary)](#14-trie-binary)
15. [Mo's Algorithm](#15-mos-algorithm)
16. [Rollback DSU](#16-rollback-dsu)
17. [Disjoint Sparse Table](#17-disjoint-sparse-table)
18. [Min Queue](#18-min-queue)
19. [Small-to-Large Merging](#19-small-to-large-merging)

---

## 1. PBDS

**Notebook:** `OS = tree<T, null_type, Cmp, rb_tree_tag, tree_order_statistics_node_update>`
**Library:** Has multiple aliases: `ordered_set`, `ordered_multiset`, `ordered_map`, `ordered_set_custom`, plus `trie` PBDS wrapper
**Reference:** KACTL doesn't include PBDS. maspypy has its own ordered set implementations.

| Aspect | Notebook | Library | Better? |
|--------|----------|---------|:-------:|
| Versatility | Basic set/multiset usage | Multiple typedefs for set/multiset/map/custom | **Library** (more complete) |
| Multiset | Uses `pair<T,id>` trick (safe) | Uses `less_equal<T>` (UB risk) | **Notebook** (safe approach) |
| Page efficiency | Compact | Too verbose for notebook | **Notebook** |

### Verdict
**Library → Notebook improvement not needed.** The library has more variants but they're too verbose for the 25-page notebook. The notebook version is the right tradeoff.

---

## 2. GP Hash Table

**Notebook:** `gp_hash_table` with custom splitmix64 hash
**Library:** Custom hash function for `gp_hash_table` / `unordered_map`
**Reference:** Standard splitmix64 approach used in CP.

`FIXED_RANDOM` is `static const` — called once. Already optimal.

### Verdict
No changes needed.

---

## 3. Rope (GNU)

**Notebook:** `gnu_cxx::rope` / `crope`

### Verdict
Standard GNU extension. No changes needed.

---

## 4. DSU

**Notebook:** 3 vectors (`par`, `rank`, `sz`)
**Library:** TWO versions:
- **V1**: Same 3-vector approach as notebook (`par, rank, sz`)
- **V2 (Min Max DSU)**: 5 vectors (`Par, rank, siz, minele, maxele`) — tracks min/max per component
**KACTL:** Single `vi e` vector with negative sizes
**maspypy:** Single `vc<int> dat` with negative sizes

| Aspect | Notebook | Library (V1) | KACTL | Better? |
|--------|----------|--------------|-------|:-------:|
| Memory (per element) | 3 ints = 12 bytes | 3 ints = 12 bytes | 1 int = 4 bytes | **KACTL (3x savings)** |
| Extra features | Size query | Size query + min/max | Size query | **Library** (has min/max) |

### ⚠️ KEY FINDING
**Neither the notebook nor the library uses the optimal single-vector approach from KACTL/maspypy.** Both use the 3-vector approach. The KACTL approach saves 66% memory AND simplifies code.

```cpp
// KACTL-style — recommended for both notebook AND library
struct dsu {
  vector<int> e;  // negative = size (root), non-negative = parent
  int cnt;
  dsu(int n) : e(n, -1), cnt(n) {}
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    if (e[x] > e[y]) swap(x, y);
    e[x] += e[y]; e[y] = x; --cnt; return true;
  }
  int size(int x) { return -e[find(x)]; }
};
```

**Memory:** 3 vectors (12N bytes) → 1 vector (4N bytes) = **66% reduction**.

**[HIGH PRIORITY]**

---

## 5. Sparse Table

**Notebook:** `vector<vector<int>> t`
**Library:** Template class with `merge` function (same approach)
**KACTL/maspypy:** Same vector-of-vectors approach

| Issue | Suggestion | Impact |
|-------|------------|--------|
| Flat array could be faster | Marginal — KACTL/maspypy use vector-of-vectors | Low |
| Log lookup each query | Precompute lookup table vs `__builtin_clz` | Low |

### Verdict
No changes needed. All implementations use the same approach.

---

## 6. Sparse Table 2D

**Notebook:** `st[11][11]` vector-of-vectors — O(NM log N log M)

Memory ~600 MB for 2048². Very high.

### Verdict
Add warning about memory constraints. Reference 2D Fenwick as alternative.

---

## 7. Fenwick Tree (BIT)

**Notebook:** `template<typename T> struct BIT` — 1-indexed, `find_kth` via binary lifting
**Library:** `struct fenwick` — 0-indexed, stores `vals` array for `set()` operation
**KACTL:** `struct FT` — 0-indexed, `lower_bound` via binary lifting

| Aspect | Notebook | Library | KACTL | Better? |
|--------|----------|---------|-------|:-------:|
| Indexing | 1-indexed | 0-indexed | 0-indexed | Matter of taste |
| find_kth | Yes (adaptive highest power) | No | Yes (fixed 1<<25) | **Notebook + KACTL** |
| set() support | No (only add) | Yes (stores vals) | No | **Library** |
| Memory | N+1 ints | 2N+1 ints | N ints | **KACTL/Notebook** |

### Verdict
**Notebook is fine.** The `set()` operation in the library can be emulated with `add(i, v - old_val)`. No optimization needed.

---

## 8. Fenwick 2D

**Notebook:** `vector<vector<ll>> bit` — (n+1)×(m+1)
**Library:** Three trees (max/min/sum) with 1-indexing

### Verdict
Notebook version is clean and correct. No changes needed.

---

## 9. BIT Range Update & Range Query

**Notebook:** 2 BITs (`bit1`, `bit2`)
**Library:** Basic BIT only (no range update)

### Verdict
Notebook is better. No changes needed.

---

## 10. Lazy Segment Tree

**Notebook:** 6 separate vectors: 5×`vector<ll>` (sm, mx, mn, ad, st) + 1×`vector<char>` (hz) = 164N bytes
**Library:** Multiple versions:
- `Smart segment tree (Lazy)`: `vector<Info> tree` + `vector<Tag> lazy` — Info struct stores sum/mx/mn/sz; Tag stores add/set
- `Lazy Segment Tree (Minimal)`: 5 separate vectors (sum, mn, mx, lz_add, lz_set) — no `hz`
**KACTL:** Pointer-based dynamic nodes with bump allocator
**maspypy:** 2 vectors (dat + laz)

| Aspect | Notebook | Library (Smart) | maspypy | Better? |
|--------|----------|-----------------|---------|:-------:|
| Number of vectors | 6 | 2 (Info + Tag) | 2 (dat + laz) | **maspypy/Library** |
| ad+st combined? | No | Yes (Tag struct) | Yes | **Library/maspypy** |

### ⚠️ KEY FINDING
The **Library's "Lazy Segment Tree (Minimal)"** already eliminates the `hz` vector by using `NO_SET = 2e18` sentinel. Reduces 6 vectors → 5.

**[HIGH PRIORITY]**

---

## 11. Persistent Segment Tree

**Notebook:** Static arrays `lc[M]`, `rc[M]`, `val[M]` (M = 4.4M, ~53 MB for N=200k)

### Verdict
Solid implementation. Static arrays avoid reallocation — good for contest use.

---

## 12. Merge Sort Tree

**Notebook:** `vector<vector<int>> tree` — 4N vectors

### Verdict
PST and Wavelet Tree (both in notebook) are strictly better alternatives. Consider adding a comparison note.

---

## 13. Wavelet Tree

**Notebook:** Recursive pointer-based tree with `vector<int> b` per node (int prefix arrays)
**Library:** TWO versions:
- **V1**: Uses `bit_vector<uint32_t>` with template params for compress + sum. Bit vector-based. Iterative traversal.
- **V2**: Uses `vector<vector<int>> pref0` for prefix counts. Full feature set: kth, sum, occ, rank, select, median, access, lower_bound, distinct values.
**maspypy:** Wavelet Matrix with `Bit_Vector`

| Aspect | Notebook | Library (V1) | Library (V2) |
|--------|----------|--------------|--------------|
| Storage per level | `vector<int>` (4 bytes/el) | `bit_vector` (~1 bit/el) | `vector<int>` (4 bytes/el) |
| Memory efficiency | Lowest | **Highest (32x savings)** | Low |
| Features | kth, count_leq, count_seg | kth, count_leq, count_seg, sum | **Full** |
| Query type | Recursive (virtual dispatch) | Iterative | Recursive (dfs) |

### ⚠️ KEY FINDING
The **Library's V1 already implements the Wavelet Matrix approach** with `bit_vector` (compact bit storage: ~1 bit per element instead of 4 bytes).

**[HIGH PRIORITY]**

---

## 14. Trie (Binary)

**Notebook:** `vector<array<int, 2>> nxt` + `vector<int> cnt` — two separate vectors
**Library:** FOUR versions. The "varsetile" version uses `struct Node { int nxt[2]; int cnt; }` in single `vector<Node> pool`.
**maspypy:** Generic `Trie<sigma>` with Aho-Corasick support.

| Aspect | Notebook | Library (varsetile) | Better? |
|--------|----------|---------------------|:-------:|
| Storage | 2 vectors (separate) | 1 vector of struct Node | **Library** (cache locality) |
| Features | Basic + count_special | Full (max/min xor, merge, mex, count) | **Library** |

### ⚠️ KEY FINDING
The **Library's "varsetile" version uses exactly the `struct Node { int nxt[2]; int cnt; }` approach** — improves cache locality (all node data in one cache line) vs two separate vectors.

**[HIGH PRIORITY]**

---

## 15. Mo's Algorithm

**Notebook:** Snake-order (odd/even block sorting)
**Library:** Same snake-order approach
**KACTL/maspypy:** Same snake-order approach

### Verdict
All implementations use snake-order. Note: comment says "Hilbert order" but code is snake-order. Minor fix.

---

## 16. Rollback DSU

**Notebook:** Single `vector<int> e` + `vector<pair<int,int>> hist`
**KACTL:** Same approach

### Verdict
Already matches KACTL. No changes needed.

---

## 17. Disjoint Sparse Table

**Notebook:** `vector<vector<int>> t` — pads to power of 2

### Verdict
Solid implementation. No urgent changes needed.

---

## 18. Min Queue

**Notebook:** `deque<int> dq` + `queue<int> q`

### Verdict
Minor optimization (index-based single deque) would halve memory but adds complexity. Keep as-is for simplicity.

---

## 19. Small-to-Large Merging

**Notebook:** `set<int>` per component (example technique)

### Verdict
Using `vector<int>` instead of `set<int>` saves ~7-8x memory. Minor change to the notebook example.

---

## Other Notable Library Implementations

### Treap (library only, not in notebook)
The library has a full **implicit Treap** with lazy reverse + range add, split/merge, range_sum, range_add, reverse, erase, set. Compact (~70 lines).

⚠️ **Known bug:** `update()` double-counts `toProp` after `push()`. See bug fix below.

### Bug Fix — Treap `update()` double-counts `toProp`

**File:** `library/Data Structures/Treap`

```cpp
void update(Node *&t) {
    t->sum = t->data + t->size * t->toProp;
    if (t->l) t->sum += t->l->sum + t->l->size * t->l->toProp;
    if (t->r) t->sum += t->r->sum + t->r->size * t->r->toProp;
}
```

After `push(t)` propagates `t.toProp` to children (incrementing `child.toProp` but NOT updating `child.sum`), the formula reads `child.sum + child.size * child.toProp` — but `child.sum` already included `child.size * old_child.toProp` from a prior `update()`. The old `toProp` is double-counted.

**Fix:** Update `child.sum` inside `push()`, then simplify `update()`:
```cpp
void push(Node *&t) {
    if (!t) return;
    if (t->rev) { /* ... swap children ... */ }
    if (t->toProp) {
        t->data += t->toProp;
        if (t->l) {
            t->l->toProp += t->toProp;
            t->l->sum += t->toProp * t->l->size;
        }
        if (t->r) {
            t->r->toProp += t->toProp;
            t->r->sum += t->toProp * t->r->size;
        }
        t->toProp = 0;
    }
}
void update(Node *&t) {
    if (!t) return;
    t->size = 1 + size(t->l) + size(t->r);
    t->sum = t->data + (t->l ? t->l->sum : 0) + (t->r ? t->r->sum : 0);
}
```

### Bug Fix — Policy Base `trie` alias self-shadow

**File:** `library/Data Structures/Policy base Data-structures`

```cpp
template<typename Key, typename Value>
using trie = trie<Key, Value, null_type, trie_prefix_search_node_update>;
```

The alias name `trie` shadows the template name `trie`, causing a compilation error.

**Fix:**
```cpp
template<typename Key, typename Value>
using trie_ds = trie<Key, Value, null_type, trie_prefix_search_node_update>;
```

### Sparse Segment Tree (library only, not in notebook)
Dynamic segment tree with pool allocator. Range add + range min/max, with or without range sum.

### Permutation Segment Tree (library only, not in notebook)
Specialized for small alphabets (K ≤ 10). Range permutation apply + range frequency query.

### Point Update Iterative Segment Tree (library + KACTL)
KACTL-style iterative segtree. Already present in the library.

---

## Summary: Library vs Notebook vs Reference

| Data Structure | Notebook Quality | Library Quality | Reference | Notes |
|---------------|:----------------:|:---------------:|:---------:|-------|
| DSU | ⚪ OK (3 vectors) | ⚪ OK (3 vectors) | 🟢 **Single vector** | Both should adopt KACTL single-vector approach |
| BIT | 🟢 Good | 🟢 Good (adds set()) | 🟢 Good | All similar |
| BIT 2D | 🟢 Good | ⚪ Min/max prefix only | — | Notebook version is cleaner for sum-only |
| Sparse Table | 🟢 Good | 🟢 Good (template) | 🟢 Good | All similar |
| Lazy SegTree | 🟢 **5 vectors (NO_SET sentinel)** | 🟢 **Smart SegTree** | 🟢 maspypy (2 vec) | Updated to eliminate hz vector |
| WT (now Wavelet Matrix) | 🟢 **Bit vector (32x savings)** | 🟢 **V1 (bit vector)** | 🟢 Wavelet Matrix | Rewritten as compact WT with iterative queries |
| Binary Trie | ⚪ 2 vectors | 🟢 **Varsetile (struct)** | 🟢 maspypy Trie | Library varsetile has the struct optimization |
| BIT Range | 🟢 Good | ⚪ Basic BIT only | — | Notebook is better |
| Treap | 🔴 Missing | 🟢 **Full implementation** (buggy) | — | Fix bug, could add to notebook |
| Sparse SegTree | 🔴 Missing | 🟢 **Full implementation** | — | Niche but useful |
| Mo's | 🟢 Good | 🟢 Good | 🟢 Good | All similar (snake-order) |

---

## 🔴 Final Ranked Recommendations

| Priority | Data Structure | Change | Rationale |
|:--------:|---------------|--------|-----------|
| **1** | **DSU** | Single `vector<int>` (negative sizes) | 66% memory reduction, code simplification, follows KACTL/maspypy | **`[DONE]`** |
| **2** | **Trie (Binary)** | `struct Node { int nxt[2]; int cnt; }` in single vector | Cache locality, follows library varsetile approach | **`[DONE]`** |
| **3** | **Lazy SegTree** | Eliminate `hz` vector via `NO_SET` sentinel | ~2.4% memory savings, follows library Minimal | **`[DONE]`** |
| **4** | **Wavelet Tree** | Bit vector storage + iterative queries (Wavelet Matrix) | 32x memory savings, follows library V1 | **`[DONE]`** |
| **5** | **Small-to-Large** | Use `vector` instead of `set` | ~7-8x memory savings, minor text change | **`[DONE]`** |
| **6** | **Treap bug fix** | Update `child.sum` in `push()` | Correctness fix | **`[DONE]`** |
| **7** | **Policy Base bug fix** | Rename `trie` alias | Compilation fix | **`[DONE]`** |
| **8** | **Sparse Table 2D** | Add memory warning | ~600 MB for 2048² max | **`[DONE]`** |
| **9** | **Mo's Algorithm** | Fix comment (Hilbert→snake) | Correctness of documentation | **`[DONE]`** |
| **10** | **Min Queue** | Index-based single deque (optional) | Halves memory (deferred — low priority) | — |

---

*Date: July 28, 2026*
*Status: Claims verified against KACTL, maspypy, and library code*
