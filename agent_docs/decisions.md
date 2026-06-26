# Decisions

## Decision Log

| Date | Decision | Rationale |
|------|----------|-----------|
| 2026-06-26 | Use modular architecture with sections/ directory | Enables parallel agent workflow |
| 2026-06-26 | Keep paracol two-column layout | Approximates original Google Docs layout |
| 2026-06-26 | Use Times font (mathptmx) | Closest available serif font in pdfLaTeX |
| 2026-06-26 | Use Courier for monospace | Matches code listing style |
| 2026-06-26 | Copy images from extracted PDF images | Ensure exact image reproduction |
| 2026-06-26 | Split monolithic .tex into 11 modular sections | Each section is a logical topic group |
| 2026-06-26 | Remove 40 redundant section files | Only 11 active files needed — others were duplicates |
| 2026-06-26 | Exclude build artifacts via .gitignore | Prevents clutter in repo |
| 2026-06-26 | Reorganize code_library/ into professional structure | templates/, references/, tools/, tricks/ etc. |
| 2026-06-26 | Add `\linespread{1.15}` | Matches original 23-page count |

## Pending Decisions

1. **Font upgrade to XeLaTeX**: Would enable exact Georgia/Arial/Cambria Math matching.
   Requires `texlive-xetex` and `fontspec` package installation.
2. **Column model change**: Consider `multicols` vs `paracol` for better match.
3. **Margin alignment**: Original uses 0.5in margins; current uses 1.0in/0.65in.
