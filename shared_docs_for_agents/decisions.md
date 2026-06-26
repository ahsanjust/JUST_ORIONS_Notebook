# Decisions

## Decision Log

| Date | Decision | Rationale |
|------|----------|-----------|
| 2026-06-26 | Use modular architecture with sections/ directory | Enables parallel agent workflow |
| 2026-06-26 | Keep paracol two-column layout | Approximates original Google Docs layout |
| 2026-06-26 | Use Charter font (via `\usepackage{charter}`) | Closest available Georgia substitute in pdfLaTeX |
| 2026-06-26 | Copy images from extracted PDF images | Ensure exact image reproduction |
| 2026-06-26 | Split monolithic .tex into 12 sections | Each section is a logical topic group |
| 2026-06-26 | Add `\linespread{1.15}` | Matches original 23-page count (was 22) |
| 2026-06-26 | Use `papersize={596pt,842pt}` for geometry | Matches original PDF's exact A4 dimensions (596×842) |
| 2026-06-26 | Fix Custom cmp pbds column position | Original has it in right column, not left |
| 2026-06-26 | Fix overfull hboxes via manual line breaks | Eliminates all overfull warnings |

## Pending Decisions

1. **Font upgrade to XeLaTeX**: Would enable exact Georgia/Arial/Cambria Math matching.
   Requires `texlive-xetex` and `lualatex-math` package installation.
2. **Column model change**: Consider `multicols` vs `paracol` for better match.
3. **Margin alignment**: Original uses 0.5in margins; current uses 1.0in/0.65in.
