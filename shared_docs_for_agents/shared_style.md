# Shared Style Guide

## Page Layout

- **Paper size**: A4 (210mm × 297mm)
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

- **Main font**: Charter (via `\usepackage{charter}`)
- **Monospace**: Latin Modern Typewriter (via `\usepackage{lmodern}` + `\usepackage[T1]{fontenc}`)
- **Math font**: Latin Modern Math (lmodern)
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

## Section Headings

- Use `\textbf{Title}` for code section headers
- No numbered sections

## Math

- Use `amsmath`, `amssymb`
- Inline math: `$...$`
- Display math: `\[...\]`

## Colors

- `xcolor` package loaded (colors used where needed)

## Graphics

- `graphicx` for images
- `tikz` for drawings
- Image directory: `images/`

## Images from PDF

5 images extracted to `/tmp/extracted_images-000.png` through `/tmp/extracted_images-004.png`
Need to be copied to `images/` directory.
