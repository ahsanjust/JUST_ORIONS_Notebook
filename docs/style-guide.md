# Shared Style Guide

## Page Layout

- **Paper size**: A4 (210mm × 297mm)
- **Exact size**: 596pt × 842pt
- **Margins**: top=1.0in, bottom=1.0in, left=0.65in, right=0.65in
- **Columns**: Two columns via `paracol` with `\columnratio{0.5}`
- **Column separation**: 14pt
- **Column separator rule**: 0.4pt

## Header/Footer

- **Style**: fancyhdr
- **Left header**: `\textbf{JUST\_ORIONS} - Jashore University of Science and Technology`
- **Right header**: `\leftmark\ -- \thepage` (section name + page number)
- **Header rule**: 0.8pt
- **No footer content**

Section names are set via `\markboth{NAME}{NAME}` at the start of each section file:
`SETUP & BASICS`, `SEGTREE / BIT`, `SPARSE / MERGE`, `TREAP`, `GRAPH`,
`TREE`, `STRING`, `TRIE / BOOTH`, `BASIS / DP`, `COMBINATORICS`, `GEOMETRY`

## Index Page

Page 1 of the notebook is a full-width index (`sections/00_index.tex`) listing
all algorithms with `\pageref` page numbers and category names. Each section
file has a `\label{sec:XX}` at its start for page referencing.

## Typography

- **Main font**: Times (via `\usepackage{mathptmx}`)
- **Monospace**: Courier (via `\usepackage{courier}`)
- **Math font**: Times (mathptmx)
- **Paragraph indent**: 0pt
- **Paragraph skip**: 5pt

## Listings (Code blocks)

- **basicstyle**: `\ttfamily\footnotesize`
- **breaklines**: true
- **breakatwhitespace**: false
- **frame**: none
- **columns**: fullflexible
- **keepspaces**: true
- **showspaces**: false
- **showstringspaces**: false
- **aboveskip**: 2pt
- **belowskip**: 2pt
- **lineskip**: 0.5pt
- **upquote**: true
- **tabsize**: 2

## Section Headings

- Use `\textbf{Title}` for code section headers
- No numbered sections

## Math

- Use `amsmath`, `amssymb`
- Inline math: `$...$`
- Display math: `\[...\]`

## Colors (Code Syntax Highlighting)

Code listings use `listings` with C++ language coloring. Every code element has a distinct color for instant visual parsing:

| Element | Color | Looks like | Purpose |
|---|---|---|---|
| Keywords | `\color{codekw}` (vivid blue) | `for`, `while`, `if`, `return` | Control flow jumps out |
| Types | `\color{codetype}` (teal) `\emph` | `int`, `vector`, `string`, `auto` | Types distinct from code |
| Strings | `\color{codestr}` (warm orange-brown) | `"hello"`, `'c'` | Warm tone, different from code |
| Comments | `\color{codecmt}` (medium gray) | `// comment` | Recedes into background |
| Numbers | `\color{codenum}` (green) | `42`, `3.14`, `1e9` | Stands out against black text |
| Preprocessor | `\color{codepre}` (purple) `\color{codepre}` | `#include`, `#define` | Directives are clearly marked |
| Identifiers | `\color{black}` (black) | `myVar`, `solve()` | Normal code text |

CP-specific types highlighted: `mt19937`, `pb_ds`, `gp_hash_table`, `ordered_set`, `tree`, `chash`, etc.

CP-specific keywords highlighted: `emplace_back`, `push_back`, `resize`, `substr`, `iota`, `fill`, `upper_bound`, `lower_bound`, etc.

## Graphics

- `graphicx` for images
- `tikz` for drawings
- Image directory: `images/`

## Images

5 images in `images/`:
- extracted_images-000.png through extracted_images-004.png
