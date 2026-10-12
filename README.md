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
├── references/             # External CP reference notebooks
│   ├── cp-reference/
│   ├── Effervescent_Code_Library/
│   ├── icpc-teamnote/
│   ├── kactl/
│   └── maspypy/
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
| 02 | **Math** | XOR Basis, FFT, NTT, Gaussian Elimination, FWHT, Berlekamp-Massey, Kitamasa |
| 03 | **Number Theory** | Extended Euclid, CRT, SPF/Möbius, Miller-Rabin, Pollard Rho, Segmented Sieve, Discrete Log |
| 04 | **Combinatorics** | Burnside, Derangements, Lucas, Bishop Placement, Inclusion-Exclusion |
| 05 | **Data Structure** | Sparse Table, PST, Fenwick, Treap, Mo's, DSU, Lazy SegTree, Wavelet Tree |
| 06 | **Strings** | Binary Trie, Booth, KMP, Z, Manacher, Suffix Array, Aho-Corasick, Hashing, Eertree |
| 07 | **Graph Theory** | SCC, Bridges, Hopcroft-Karp, Dinic, HLD, Centroid Decomp, 2-SAT, MCMF, Euler Tour |
| 08 | **Geometry** | Closest Pair, Polygon Ops, Convex Hull, Half-Plane Intersection, Minkowski Sum |
| 09 | **Dynamic Programming** | SOS DP, Knuth Opt, Li Chao Tree, Subset Sum Bitset, Max Rectangular Sum |
| 10 | **Others** | Game Theory, Sprague-Grundy, Bit Hacks, Sum over Digits, Zobrist Hashing |

---

## Constraints

- **Max pages:** 25 (IUPC/ICPC limit)
- **Layout:** 3-column landscape, 10pt font, minted syntax highlighting
- **Language:** C++17

---

## Code Formatting & Style Guide

All algorithm templates in this repository adhere to a unified formatting style configured in `.clang-format` (based on Google C++ style):

- **Indentation**: 2 spaces (no tabs)
- **Column Limit**: 120 columns
- **Single-Line Conditionals & Loops**: For `if()`, `for()`, and `while()` conditions without braces (`{}`), the statement **must remain on the same line** to conserve vertical space and maximize density for the printed notebook.
  - Configured settings:
    ```yaml
    BasedOnStyle: Google
    IndentWidth: 2
    ColumnLimit: 120
    AllowShortIfStatementsOnASingleLine: AllIfsAndElse
    AllowShortLoopsOnASingleLine: true
    AllowShortBlocksOnASingleLine: Never
    AllowShortFunctionsOnASingleLine: Inline
    ```
  - Example:
    ```cpp
    if (mid) swap(t[u].line, nw);
    if (l == r) return;
    for (int i = 0; i < n; i++) cin >> a[i];
    while (q--) solve();
    ```

### Format Commands
To reformat all C++ snippets in `notebook_library/`:
```bash
find notebook_library/ -name "*.cpp" -exec clang-format -i {} +
```

### Rules for Agents & Contributors (Adding New Sections & Space Optimization)

> ⚠️ **CRITICAL INSTRUCTIONS FOR ALL AGENTS & CONTRIBUTORS:**
> This repository produces the printed competition reference notebook for ICPC / IUPC contests. Any mistake or page overflow can severely compromise contest performance. Whenever adding new sections, modifying algorithms, or optimizing space, you **MUST** strictly adhere to the following rules:

1. **Strict 25-Page Limit (`<= 25 Pages`)**:
   - The reference notebook has a hard limit of **25 pages** (`pdfinfo notebook/main.pdf | grep Pages`).
   - Under no circumstances may changes cause the document to expand to 26 pages or more.
   - Always verify that the final page has a comfortable margin buffer to absorb future additions.

2. **Horizontal Space Optimization & Density ("Best Use of Right-Side Empty Spaces")**:
   - **Column Character Limit**: The layout is a 3-column landscape document with 9pt minted font. The effective column width is **~48–52 characters per line**.
   - **Avoid Automatic Wrapping**: Any line exceeding ~50 characters will automatically wrap with a red arrow `\ensuremath{\hookrightarrow}`, consuming an extra vertical line and diminishing readability.
   - **Optimize Right-Side Space**:
     - Collapse single-line conditionals and loops onto the same line: `if (l == r) return;`, `for (int i = 0; i < n; i++) cin >> a[i];`.
     - Compact short structs and classes: `struct Edge { int to, edge_id; };` instead of 3 separate lines.
     - Inline trivial getters, operators, and methods: `T jumpK(T val, T k) { return kth(count_leq(val) + k); }`.
     - Group related variable declarations: `int n = a.size(), m = b.size();`, `ll dx = max(0LL, rx - lx), dy = max(0LL, ry - ly);`.
     - Eliminate dangling single-brace lines (`}`) when a block `{ ... }` comfortably fits on a single line within the 48-character limit.

3. **Type Aliases & Shorthand Conventions**:
   - **Always use `ld` instead of `long double`**: Never use `long double` in code snippets, algorithm templates, or LaTeX sections (especially in **Geometry**). Always use `ld`.
   - **Always use `ll` instead of `long long`**: Never use `long long`. Always use `ll`.
   - The team's contest setup pre-declares `using ll = long long;` and `using ld = long double;`. Using `ld` and `ll` maximizes character density, prevents line wrapping, and saves essential vertical space.

4. **Bidirectional Synchronization (`notebook/sections/` ↔ `notebook_library/`)**:
   - Every algorithm snippet in `notebook/sections/*.tex` must have an identical, standalone counterpart in `notebook_library/<Section>/`.
   - When editing or adding code in a LaTeX section, always update or create the corresponding `.cpp` file in `notebook_library/`.
   - Do not allow the LaTeX sections and the source snippet files to drift out of sync.

5. **Notebook Integrity & Algorithmic Correctness ("Never Destroy the Notebook")**:
   - Never compromise correctness, numerical stability, or edge-case handling for brevity.
   - Text explanations in LaTeX must be concise, mathematically exact, and highlight crucial competitive programming pitfalls (e.g., coordinate clamping, sign multiplication traps, $O(1)$ vs $O(\log N)$ tradeoffs).

6. **Mandatory Build & Verification Workflow**:
   - Run `make build` to ensure LaTeX compiles cleanly (0 errors, no broken minted environments).
   - Check `pdfinfo notebook/main.pdf | grep Pages` to confirm that page count is strictly $\le 25$.
   - Inspect page layout visually (using `pdftoppm` or `make view`) to verify clean columns with no ugly line-wrapping arrows.
   - Run tests (`python3 test_harness/run_tests.py`) to confirm snippet integrity.

---

## About

**JUST_ORIONS** competes in IUPCs — ICPC-style contests held across Bangladeshi universities
(BUET, SUST, CUET, AUST, UIU, etc.). This notebook is our printed reference document,
optimized for maximum algorithmic density within the page budget.

---

*Built with LaTeX · Powered by minted · Maintained by JUST_ORIONS*
