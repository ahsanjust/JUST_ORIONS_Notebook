# Shared Style Guide — JUST_ORIONS Notebook

## Document Class & Page Layout
- **Document class:** `article`, 10pt, A4 paper
- **Page size:** 596×842pt (exact A4 match)
- **Geometry:** top=1.0in, bottom=1.0in, left=0.65in, right=0.65in
- **Column layout:** `paracol` package, 2 columns, `\columnratio{0.5}`
- **Column separator:** 14pt width, 0.4pt rule

## Fonts
- **Text font:** Charter (`\usepackage{charter}`) — closest pdfLaTeX alternative to Georgia
- **Code font:** Latin Modern Typewriter (via `lmodern` + `listings` basicstyle=\ttfamily\footnotesize)
- **Math font:** Latin Modern (via `lmodern`)
- **Font encoding:** T1 (`\usepackage[T1]{fontenc}`)
- **Line spacing:** `\linespread{1.15}` (matches Google Docs default ~1.15)

## Headers & Footers
- **Package:** `fancyhdr`
- **Head rule width:** 0.8pt
- **Left header:** `\textbf{JUST\_ORIONS} - Jashore University of Science and Technology`
- **Right header:** `\thepage`
- **Footer:** empty

## Spacing
- **Column separation:** 14pt
- **Column separator rule:** 0.4pt
- **Paragraph skip:** 5pt
- **Paragraph indent:** 0pt

## Code Listings
- **Package:** `listings`
- **Basic style:** `\ttfamily\footnotesize`
- **Break lines:** true
- **Break at whitespace:** false
- **Frame:** none
- **Columns:** fullflexible
- **Keep spaces:** true
- **Show spaces:** false
- **Show string spaces:** false
- **Above skip:** 2pt
- **Below skip:** 2pt
- **Line skip:** 0.5pt

## Typography Conventions
- **Section titles:** `\textbf{\Large ...}` for main topics
- **Subsection labels:** `\textit{...}` for sub-labels (e.g., "Custom cmp pbds:", "Fenwick 2D")
- **Math formulas:** inline `$...$` and display `\[...\]`
- **Comments in code:** use `//` inside lstlisting

## Packages Used
- geometry, paracol, fancyhdr, listings, graphicx, amsmath, amssymb, fontenc, lmodern, xcolor, charter, caption, tikz

## Column Flow
- Content flows left→right via `\switchcolumn`
- Each `\switchcolumn` moves to the next column
- All section files are `\input{}` inside the paracol environment
- Section files may contain `\switchcolumn` calls

## Images
- Directory: `images/`
- Extracted from original PDF: extracted_images-000.png through extracted_images-004.png
- Used in geometry section (tikz diagrams for geometric shapes)
