# 📘 JUST_ORIONS — Team Reference Notebook

> **Jashore University of Science and Technology** · Competitive Programming Team

A battle-tested 25-page reference notebook for **ICPC-style contests** (IUPCs), containing
hand-picked algorithms, data structures, and formulas — compiled into a compact two-column
LaTeX PDF that teams can bring into contest.

---

## 📂 Repository Structure

```
JUST_ORIONS_Notebook/
├── notebook/               # LaTeX source → compiled PDF
│   ├── main.tex            # Master document
│   ├── main.pdf            # Compiled output (25-page reference)
│   └── sections/           # 11 modular algorithm sections
│       ├── 01_build_and_basics.tex
│       ├── 02_persistent_segtree.tex
│       ├── 03_sparse_table.tex
│       ├── 04_treap.tex
│       ├── 05_graph_algorithms.tex
│       ├── 06_tree_algorithms.tex
│       ├── 07_string_algorithms.tex
│       ├── 08_trie_and_booth.tex
│       ├── 09_basis_and_dp.tex
│       ├── 10_combinatorics.tex
│       └── 11_geometry_and_misc.tex
│
├── library/                # CP algorithm library (git submodule)
│   ├── templates/          # 16 self-contained contest templates
│   ├── data_structures/    # Segment Tree, BIT, DSU, Trie, Treap...
│   ├── graph/              # SCC, LCA, HLD, Flows, Matching...
│   ├── string/             # KMP, Z, Hashing, Suffix Array, Aho-Corasick...
│   ├── math/               # FFT, Combinatorics, Matrix Exp...
│   ├── number_theory/      # Sieves, Mint, CRT, Pollard Rho...
│   ├── dynamic_programming/# Digit DP, SOS DP, CHT, Bitmask DP...
│   ├── geometry/           # Convex Hull, Line Intersection, Closest Pair...
│   ├── bits/               # Basis Vectors, FWHT, XOR tricks...
│   ├── tricks/             # Algorithmic tricks and techniques
│   └── references/         # External libraries (KACTL, ICPC teamnote...)
│
└── docs/                   # Project documentation
    ├── context.md          # Project context & architecture overview
    ├── progress.md         # Section completion tracker
    ├── decisions.md        # Design decision log
    ├── issues.md           # Known issues & fixes
    └── style-guide.md      # LaTeX style & typography guide
```

---

## 🚀 Quick Start

### Prerequisites

```bash
# Ubuntu / Debian
sudo apt install texlive-full python3-pygments

# Arch Linux
sudo pacman -S texlive-most python-pygments
```

### Build the Notebook

```bash
make          # Build PDF (double-pass for TOC)
make view     # Build + open PDF
make clean    # Remove build artifacts
```

Or manually:

```bash
cd notebook
pdflatex -shell-escape main.tex
pdflatex -shell-escape main.tex   # second pass for correct TOC page numbers
```

> ⚠️ The `-shell-escape` flag is **required** — the `minted` package uses it for syntax highlighting.

---

## 📋 Notebook Contents

| # | Section | Key Algorithms |
|---|---------|----------------|
| 01 | **Setup & Basics** | Sublime build, PBDS, GP Hash, DSU |
| 02 | **Segtree / BIT** | Persistent Seg Tree, Fenwick 1D/2D, Range Update |
| 03 | **Sparse / Merge** | Sparse Table, Sparse Table 2D, Merge Sort Tree |
| 04 | **Treap** | Implicit Treap with lazy (reverse, range add, sum) |
| 05 | **Graph** | SCC (Kosaraju), Bridges, Hopcroft-Karp, Dinic's |
| 06 | **Tree** | Binary Lifting, Euler Tour, HLD, Centroid Decomp, LCA |
| 07 | **String** | KMP, Z, Manacher, Suffix Array + LCP, Aho-Corasick, Trie |
| 08 | **Trie / Booth** | Booth's Algo, Extended GCD, CRT, SPF/Möbius, Miller-Rabin, MatExp |
| 09 | **Basis / DP** | Basis Vector, SOS DP, LIS, Subset Sum bitset, Submasks |
| 10 | **Combinatorics** | Burnside's Lemma, Inclusion-Exclusion, Bishop Placement |
| 11 | **Geometry & Misc** | Closest Pair, Polygon, Convex Hull, Mo's Algorithm, Pollard Rho |

---

## 📏 Constraints

- **Max pages:** 25 (IUPC/ICPC limit) — currently ~21 pages (~4 pages of budget remaining)
- **Layout:** 3-column landscape, 9pt font, minted syntax highlighting
- **Language:** C++17

---

## 🏆 About

**JUST_ORIONS** competes in IUPCs — ICPC-style contests held across Bangladeshi universities
(BUET, SUST, CUET, AUST, UIU, etc.). This notebook is our printed reference document,
optimized for maximum algorithmic density within the page budget.

---

*Built with LaTeX · Powered by minted · Maintained by JUST_ORIONS*
