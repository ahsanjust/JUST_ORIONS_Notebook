# Handover Notes

## Project Context: What Is This?

**JUST_ORIONS** is a competitive programming team from **Jashore University of Science and Technology (JUST)**, Bangladesh.

This repository contains the team's **25-page reference notebook** for **IUPCs (Inter University Programming Contests)**.

### What is an IUPC?

IUPCs are ICPC-style team programming contests held across Bangladeshi universities (BUET, SUST, CUET, AUST, UIU, etc.). Multiple IUPCs happen every year. Key rules:
- **3 members** per team from the same university
- **5 hours** to solve 7–13 algorithmic problems
- ICPC scoring (most problems solved, ties broken by penalty time)
- Teams can bring a **printed reference document** (max 25 pages)

### What is the 25-page notebook?

The **team reference document** (also called codebook, team notebook, or template) is a printed booklet teams bring to contests. The standard limit across ICPC regionals and IUPCs is **25 pages maximum**. It contains algorithms, data structures, code snippets, and formulas the team might need — compressed into compact two-column LaTeX to maximize content per page.

The notebook is **not** meant to teach algorithms — it's a reference for experienced contestants who already know the material but need to avoid coding complex algorithms from scratch under time pressure.

### Repository Purpose

| Component | Purpose |
|---|---|
| `notebook/` | The 25-page LaTeX notebook itself (compiled PDF = team reference doc) |
| `code_library/` | Algorithm implementations + external CP libraries used to build the notebook |
| `agent_docs/` | Coordination docs for AI agents working on this project |

The goal is to produce a PDF that matches the original Google Docs version as closely as possible in layout, pagination (23–25 pages), fonts, and content.

## Current State

- Monolithic `JUST_ORIONS_Notebook.tex` (reference) compiles successfully
- Modular `main.tex` + 11 section files in `sections/` compiles identically (23 pages)
- Redundant files (old s01-s28, topic files, setup.tex) have been removed
- Build artifacts (.aux, .log) excluded via `.gitignore`
- code_library/ directory reorganized with professional structure
- Both repos pushed to GitHub

## Architecture

```
Template/
├── notebook/                   # LaTeX notebook project
│   ├── main.tex               # Master document (11 includes)
│   ├── JUST_ORIONS_Notebook.tex  # Monolithic (backup)
│   ├── JUST_ORIONS Notebook_Original.pdf
│   ├── sections/               # 00_index.tex + 11 modular .tex files
│   └── images/                 # 5 PNG images
├── code_library/               # CP code library (nested repo)
│   ├── templates/              # 16 standalone .cpp templates
│   ├── number_theory/          # Sieves, modular arithmetic, etc.
│   ├── data_structures/        # Segment Tree, BIT, DSU, Trie, etc.
│   ├── graph/                  # SCC, LCA, HLD, Flow, etc.
│   ├── dynamic_programming/    # Digit DP, SOS DP, CHT, etc.
│   ├── math/                   # FFT, combinatorics, matrices
│   ├── string/                 # KMP, Z, Hashing, Suffix Array
│   ├── geometry/               # Geometric algorithms
│   ├── bits/                   # Basis vectors, FWHT
│   ├── tricks/                 # Algorithmic tricks
│   ├── misc/                   # Miscellaneous
│   ├── unsolved_problems/      # Problem tracker
│   ├── references/             # External CP libraries
│   └── tools/                  # debug-tips.txt, stl-ref.txt
└── agent_docs/                 # Agent coordination docs
    ├── progress.md
    ├── issues.md
    ├── decisions.md
    ├── shared_style.md
    └── handover.md
```

## Key Metrics

- Notebook: 21 pages (index page + 20 content pages)
- Index page with page-numbered algorithm listing on page 1
- Section-aware page headers showing current category on every page
- 11 modular section files (replaced 28 old files + 12 topic files)
- 16 standalone templates in code_library/templates/
- code_library: ~68MB, ~2000 files across personal code + 4 external repos

## Remaining Work

1. Font upgrade to XeLaTeX for exact Georgia/Arial/Cambria Math matching
2. Column layout fine-tuning (paracol vs multicols)
3. Pixel-level PDF comparison with original
4. Image embedding verification

## Key Constraint

The final PDF must be **≤25 pages** (the IUPC/ICPC limit). Currently at 21 pages, leaving ~4 pages of breathing room for fixes and additions.
