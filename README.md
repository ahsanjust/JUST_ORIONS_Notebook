# JUST_ORIONS — Team Reference Notebook

> **Jashore University of Science and Technology** · Competitive Programming Team

A battle-tested 25-page reference notebook for **ICPC-style contests** (IUPCs), containing
hand-picked algorithms, data structures, and formulas — compiled into a compact three-column
LaTeX PDF that teams can bring into contest.

---

## Repository Structure

```
Template/
├── library/                # CP algorithm library (all code)
│   ├── Bits/               # Basis Vectors, FWHT, XOR tricks
│   ├── Data Structures/    # Segment Tree, BIT, DSU, Trie, Treap...
│   ├── Dynamic Programming/# Digit DP, SOS DP, CHT, Bitmask DP...
│   ├── Geometry/           # Convex Hull, Line Intersection, Closest Pair...
│   ├── Graph/              # SCC, LCA, HLD, Flows, Matching...
│   ├── Math/               # FFT, Combinatorics, Matrix Exp...
│   ├── Number Theory/      # Sieves, Mint, CRT, Pollard Rho...
│   ├── String/             # KMP, Z, Hashing, Suffix Array, Aho-Corasick...
│   ├── Tools/              # Debug tips, STL ref
│   ├── Tricks/             # Algorithmic tricks and techniques
│   └── Others/             # Misc utilities
│
├── notebook_library/       # Snippets organized by notebook section
│   ├── Setup & Basics/
│   ├── Data_Structure/
│   ├── Graph_Theory/
│   ├── Number_Theory/
│   ├── Combinatorics/
│   ├── Math/
│   ├── Strings/
│   ├── Geometry/
│   ├── Dynamic_Programming/
│   └── Others/
│
├── notebook/               # LaTeX source → compiled PDF
│   ├── main.tex            # Master document
│   ├── main.pdf            # Compiled output (25-page reference)
│   ├── issues.md           # Known issues
│   └── sections/           # 10 modular algorithm sections
│       ├── 01_setup_and_basics.tex
│       ├── 02_math.tex
│       ├── 03_number_theory.tex
│       ├── 04_combinatorics.tex
│       ├── 05_data_structure.tex
│       ├── 06_strings.tex
│       ├── 07_graph_theory.tex
│       ├── 08_geometry.tex
│       ├── 09_dynamic_programming.tex
│       └── 10_others.tex
│
├── test_harness/           # Test scripts for library code
│   ├── extract_snippets.py
│   ├── generate_tests.py
│   ├── run_tests.py
│   ├── test_runner.py
│   └── common_macros.h
│
├── docs/                   # Reference materials
│   ├── Catalog-Codeforces.pdf
│   ├── STRESSTEST_GUIDE.md
│   └── STRESSTEST_LOG.md
│
├── Makefile                # Build system for the notebook PDF
├── README.md
└── .gitignore
```

---

## Quick Start

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

> The `-shell-escape` flag is **required** — the `minted` package uses it for syntax highlighting.

---

## Notebook Contents

| # | Section | Key Algorithms |
|---|---------|----------------|
| 01 | **Setup & Basics** | Sublime build, PBDS, GP Hash, Fast I/O, Debug |
| 02 | **Math** | XOR Basis, Matrix Exp, FFT, NTT, Lagrange Interpolation, Gaussian Elimination, FWHT, Berlekamp-Massey |
| 03 | **Number Theory** | Extended Euclid, CRT, SPF/Möbius, Miller-Rabin, Pollard Rho, Segmented Sieve, Discrete Log |
| 04 | **Combinatorics** | Burnside, Derangements, Lucas, Bishop Placement, Inclusion-Exclusion |
| 05 | **Data Structure** | Sparse Table, Merge Sort Tree, PST, Fenwick, Treap, Mo's, DSU, Lazy SegTree, Wavelet Tree |
| 06 | **Strings** | Binary Trie, Booth, KMP, Z, Manacher, Suffix Array, Aho-Corasick, Hashing, Eertree |
| 07 | **Graph Theory** | SCC, Bridges, Hopcroft-Karp, Dinic, HLD, Centroid Decomp, 2-SAT, MCMF, Euler Tour |
| 08 | **Geometry** | Closest Pair, Polygon Ops, Convex Hull, Half-Plane Intersection, Minkowski Sum |
| 09 | **Dynamic Programming** | SOS DP, Knuth Opt, Li Chao Tree, Subset Sum Bitset, Max Rectangular Sum |
| 10 | **Others** | Game Theory, Sprague-Grundy, Bit Hacks, Sum over Digits, Zobrist Hashing |

---

## Constraints

- **Max pages:** 25 (IUPC/ICPC limit) — currently ~21 pages (~4 pages of budget remaining)
- **Layout:** 3-column landscape, 10pt font, minted syntax highlighting
- **Language:** C++17

---

## About

**JUST_ORIONS** competes in IUPCs — ICPC-style contests held across Bangladeshi universities
(BUET, SUST, CUET, AUST, UIU, etc.). This notebook is our printed reference document,
optimized for maximum algorithmic density within the page budget.

---

*Built with LaTeX · Powered by minted · Maintained by JUST_ORIONS*
