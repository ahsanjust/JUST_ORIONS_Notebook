# Context & Architecture

## What Is This?

**JUST_ORIONS** is a competitive programming team from **Jashore University of Science and Technology (JUST)**, Bangladesh.

This repository contains the team's **25-page reference notebook** for **IUPCs (Inter-University Programming Contests)**.

### What is an IUPC?

IUPCs are ICPC-style team contests held across Bangladeshi universities (BUET, SUST, CUET, AUST, UIU, etc.). Key rules:
- **3 members** per team, same university
- **5 hours** to solve 7–13 algorithmic problems
- ICPC scoring: most problems solved, ties broken by penalty time
- Teams may bring a **printed reference document (max 25 pages)**

### What is the Notebook?

The **team reference document** (codebook) is a printed booklet teams bring to contest.
It contains algorithms, data structures, code snippets, and formulas — compressed into
compact multi-column LaTeX to maximize content per page.

> The notebook is **not** meant to teach — it's a reference for contestants who know the
> material but need to avoid coding complex algorithms from scratch under time pressure.

---

## Repository Map

| Path | Purpose |
|------|---------|
| `notebook/` | LaTeX source → 25-page PDF contest reference |
| `library/` | Full CP algorithm library (git submodule) |
| `docs/` | Project documentation for agents and contributors |

---

## Current State

- `main.tex` + 11 section files in `sections/` → compiles to **~21 pages**
- 3-column landscape layout with minted syntax highlighting
- Build artifacts fully excluded via `.gitignore`
- `library/` (submodule) organized into category directories
- Both repos pushed to GitHub
- `make build` / `make view` / `make clean` available via `Makefile`

---

## Architecture

```
JUST_ORIONS_Notebook/
├── README.md                   # Project overview
├── Makefile                    # Build system (make build/view/clean)
├── .gitignore
├── .gitmodules
│
├── notebook/                   # LaTeX notebook
│   ├── main.tex                # Master document (11 \input{} sections)
│   ├── main.pdf                # Compiled output (git-ignored)
│   └── sections/
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
├── library/                    # CP algorithm library (submodule)
│   ├── templates/              # 16 standalone contest templates
│   ├── data_structures/        # Segment Tree, BIT, DSU, Trie, etc.
│   ├── graph/                  # SCC, LCA, HLD, Flow, Matching
│   ├── string/                 # KMP, Z, Hashing, Suffix Array
│   ├── math/                   # FFT, Combinatorics, Matrix Exp
│   ├── number_theory/          # Sieves, Mint, CRT, Pollard Rho
│   ├── dynamic_programming/    # Digit DP, SOS DP, CHT, Bitmask
│   ├── geometry/               # Convex Hull, Line Intersect, etc.
│   ├── bits/                   # Basis Vectors, FWHT
│   ├── tricks/                 # Algorithmic tricks
│   ├── references/             # External: KACTL, icpc-teamnote...
│   └── tools/                  # debug-tips.txt, stl-ref.txt
│
└── docs/                       # Documentation
    ├── context.md              # ← this file
    ├── progress.md             # Section completion tracker
    ├── decisions.md            # Design decision log
    ├── issues.md               # Known issues & workarounds
    └── style-guide.md          # LaTeX typography & code style
```

---

## Key Metrics

| Metric | Value |
|--------|-------|
| Current pages | ~21 pages |
| Page budget remaining | ~4 pages |
| Layout | 3-column landscape, 9pt font |
| Sections | 11 modular `.tex` files |
| Library templates | 16 standalone `.cpp` files |
| Library total | ~68MB, ~2000 files |

---

## Remaining Work

1. **Fill remaining ~4 pages** with missing algorithms
2. **Font upgrade** — XeLaTeX + fontspec for exact Georgia/Arial/Cambria Math
3. **Column layout** — evaluate `multicols` vs `paracol`
4. **Margin tuning** — original uses 0.5in; current uses 0.2in

---

## Build

```bash
make          # double-pass build (required for correct TOC)
make view     # build + open PDF
make clean    # remove build artifacts
```

**Requirements:** `texlive-full` + `python3-pygments` (for minted `-shell-escape`)

---

## Key Constraint

> The final PDF must be **≤ 25 pages** — the IUPC/ICPC hard limit.
> Currently at ~21 pages with ~4 pages of headroom.
