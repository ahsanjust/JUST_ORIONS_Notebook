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
- **Right header**: page number (`\thepage`)
- **Header rule**: 0.8pt
- **No footer content**

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

Code listings use `listings` with C++ language coloring:

| Element | Color | Usage |
|---|---|---|
| Keywords | `\color{codekw}` (dark blue) | `int`, `for`, `while`, `struct`, `auto`, etc. |
| Strings | `\color{codestr}` (dark green) | `"hello"`, `'c'` |
| Comments | `\color{codecmt}` (gray) | `// comment`, `/* comment */` |
| Numbers | `\color{codenum}` (dark red) | `42`, `3.14`, `0xFF` |
| Identifiers | `\color{black}` (black) | variable/function names |

Additional CP-specific keywords highlighted: `mt19937`, `pb_ds`, `gp_hash_table`, `ordered_set`, `tree`, etc.

## Graphics

- `graphicx` for images
- `tikz` for drawings
- Image directory: `images/`

## Images

5 images in `images/`:
- extracted_images-000.png through extracted_images-004.png
