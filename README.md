# 📘 JUST_ORIONS — Team Reference Notebook

> **Jashore University of Science and Technology** · Competitive Programming Team

A battle-tested 25-page reference notebook for **ICPC-style contests** (IUPCs), containing
hand-picked algorithms, data structures, and formulas — compiled into a compact two-column
LaTeX PDF that teams can bring into contest.

---

## 📂 Repository Structure

```
Template/
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
├── notebook/               # LaTeX source → compiled PDF
│   ├── main.tex            # Master document
│   ├── main.pdf            # Compiled output (25-page reference)
│   └── sections/           # 9 modular algorithm sections
│       ├── 01_setup_and_basics.tex
│       ├── 02_data_structure.tex
│       ├── 03_graph_theory.tex
│       ├── 04_number_theory.tex
│       ├── 05_combinatorics.tex
│       ├── 06_math.tex
│       ├── 07_strings.tex
│       ├── 08_geometry.tex
│       └── 09_others.tex
│
├── analysis/               # Gap analysis reports vs major CP resources
│   ├── catalog-analysis.md          # CF catalog cross-reference
│   ├── catalog-analysis-kactl.md    # KACTL cross-reference
│   └── catalog-analysis-cpalgo.md   # cp-algorithms cross-reference
│
├── docs/                   # Reference PDFs and other documents
│   ├── Backup_notebook.pdf
│   └── Catalog-Codeforces.pdf
│
├── Makefile                # Build system for the notebook PDF
├── README.md
├── .gitignore
└── .gitmodules             # library/ submodule definition
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
| 01 | **Setup & Basics** | Sublime build, PBDS, GP Hash, Fast I/O, Debug |
| 02 | **Data Structure** | Sparse Table, Merge Sort Tree, PST, Fenwick, Treap, Mo's, DSU, Lazy SegTree |
| 03 | **Graph Theory** | SCC, Bridges, Hopcroft-Karp, Dinic, HLD, Centroid Decomp, 2-SAT, MCMF |
| 04 | **Number Theory** | Extended Euclid, CRT, SPF/Möbius, Miller-Rabin, Pollard Rho, Segmented Sieve |
| 05 | **Combinatorics** | Burnside, Stirling, Catalan, Lucas, Stars & Bars, Generating Functions |
| 06 | **Math** | XOR Basis, Matrix Exp, FFT, NTT, Lagrange Interpolation, Digit DP |
| 07 | **Strings** | Binary Trie, Booth, KMP, Z, Manacher, Suffix Array, Aho-Corasick, Hashing |
| 08 | **Geometry** | Closest Pair, Polygon Ops, Convex Hull, Half-Plane Intersection |
| 09 | **Others** | Game Theory, SOS DP, FWHT, Knuth Opt, Li Chao Tree, Gaussian Elimination, BM, Wavelet Tree |

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
