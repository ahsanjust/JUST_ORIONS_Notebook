# Issues Tracker — JUST_ORIONS Notebook

## Known Issues

### 1. Page Count Difference (22 vs 23)
- **Severity:** Medium
- **Description:** Original has 23 pages, our generated version has 22 pages
- **Root Cause:** Different rendering engines (Google Docs Skia/PDF vs pdfTeX) produce different line breaking and font metrics, causing content to flow differently across pages
- **Status:** Under investigation
- **Mitigation:** All content is present; page break differences are expected when recreating from a different rendering engine

### 2. Font Differences
- **Severity:** Medium
- **Description:** Original uses Google Docs default fonts (likely Times New Roman for body, Courier New for code). Our version uses Charter for body and Latin Modern Typewriter for code.
- **Root Cause:** Original was created in Google Docs, not LaTeX
- **Status:** Noted
- **Mitigation:** Consider switching to `\usepackage{times}` and `\usepackage{courier}` to match closer

### 3. Code Indentation Differences
- **Severity:** Low
- **Description:** Some code blocks in the original have different indentation levels compared to our version
- **Root Cause:** Different text rendering and line-wrapping behavior between Google Docs and LaTeX listings
- **Status:** Noted

### 4. Overfull hbox Warnings (3)
- **Severity:** Low
- **Description:** Three minor overfull hbox warnings:
  - "Minimum Lexicographic Rotation(Booth's Algorithm)" title
  - GCD property 15 (long formula)
  - "Segment Area" geometry formula
- **Status:** Present in both original compilation and current version

## Resolved Issues
- All section content extracted and placed correctly
- Modular architecture working (11 section files + main.tex)
- paracol column switching preserved correctly
- All code listings compile without errors
- Math formulas render correctly
- TikZ diagrams render correctly
