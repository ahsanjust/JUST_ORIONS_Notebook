# Handover Notes

## Current State

- Monolithic file `JUST_ORIONS_Notebook.tex` works and compiles
- Modular architecture created with `main.tex` + 28 section files in `sections/`
- Modular version compiles and produces identical output to monolithic
- Shared documentation in `shared_docs/`
- 5 images extracted from original PDF to `images/`

## Architecture

```
main.tex              - Master document (Overleaf-compatible)
sections/
  s01.tex - s28.tex   - Individual column segments
images/
  extracted_images-*.png - 5 images from original PDF
shared_docs/
  progress.md         - Task tracking
  issues.md           - Known issues
  shared_style.md     - Style guide
  decisions.md        - Decision log
  handover.md         - This file
```

## Key Findings

1. **Page count**: Original = 23 pages, LaTeX = 22 pages. This is the critical issue.
2. **Page size**: Original = 596x842 pts, LaTeX A4 = 595.276x841.89 pts. Tiny difference may cause pagination shift.
3. **Fonts**: Original uses Google Docs (Georgia/Arial/etc), LaTeX uses Charter + Latin Modern.
4. **Images**: Need to be included with \includegraphics where appropriate.
5. **Content differences**: Various minor differences exist in text extraction comparison.

## Next Steps

1. **Fix page size** to exactly 596x842 pts using `[papersize={596pt,842pt}]` in geometry.
2. **Embed images** using \includegraphics for the 5 extracted images.
3. **Address pagination** by adjusting margins, spacing, or font sizes to match 23 pages.
4. **Run pixel-level comparison** between original and generated PDFs.
5. **Iteratively fix** all visual differences.
