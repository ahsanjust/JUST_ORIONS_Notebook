# Progress

## Section Status

| Section File | Content | Status |
|---|---|---|
| `01_build_and_basics.tex` | Sublime Build, PBDS, GP Hash, DSU | ✅ Done |
| `02_persistent_segtree.tex` | Persistent Seg Tree, Fenwick BIT 1D/2D, Range Update | ✅ Done |
| `03_sparse_table.tex` | Sparse Table, Sparse Table 2D, Merge Sort Tree, Kth Smallest | ✅ Done |
| `04_treap.tex` | Implicit Treap (lazy: reverse, range add, sum) | ✅ Done |
| `05_graph_algorithms.tex` | SCC (Kosaraju), Bridges, Hopcroft-Karp, Dinic's Max Flow | ✅ Done |
| `06_tree_algorithms.tex` | Binary Lifting, Euler Tour, HLD, Centroid Decomp ×2, LCA | ✅ Done |
| `07_string_algorithms.tex` | KMP, Z, Manacher, Suffix Array + LCP, Aho-Corasick, Binary Trie | ✅ Done |
| `08_trie_and_booth.tex` | Trie ops, Booth's, GCD props, Ext Euclid, CRT, SPF/Möbius, Miller-Rabin, MatExp | ✅ Done |
| `09_basis_and_dp.tex` | Basis Vector (full), SOS DP, LIS, Subset Sum, Submasks, Derangements, Catalan | ✅ Done |
| `10_combinatorics.tex` | Burnside's Lemma, Inclusion-Exclusion DP, Bishop Placement, EPS | ✅ Done |
| `11_geometry_and_misc.tex` | Geometry formulas, Closest Pair, Polygon, Convex Hull, Mo's, Pollard Rho | ✅ Done |

---

## Page Budget

| Metric | Value |
|--------|-------|
| Max allowed | 25 pages |
| Current output | ~21 pages |
| **Remaining budget** | **~4 pages** |

---

## File Structure

```
notebook/
├── main.tex                    # Master document
├── main.pdf                    # Compiled output (git-ignored)
└── sections/
    ├── 01_build_and_basics.tex
    ├── 02_persistent_segtree.tex
    ├── 03_sparse_table.tex
    ├── 04_treap.tex
    ├── 05_graph_algorithms.tex
    ├── 06_tree_algorithms.tex
    ├── 07_string_algorithms.tex
    ├── 08_trie_and_booth.tex
    ├── 09_basis_and_dp.tex
    ├── 10_combinatorics.tex
    └── 11_geometry_and_misc.tex
```

---

## Build

```bash
make          # from repo root — double-pass build
make view     # build + open PDF
make clean    # remove artifacts
```

> Requires `-shell-escape` for `minted`. Dependencies: `texlive-full`, `python3-pygments`.
