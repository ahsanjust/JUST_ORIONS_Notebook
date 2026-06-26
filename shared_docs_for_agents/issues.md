# Issues

## Current Issues

1. **Font mismatch**: Original uses Georgia (body), Arial (code), Cambria Math (math), Spectral (header).
   Current LaTeX uses Charter (body), Latin Modern Mono (code), Latin Modern Math (math).
   To fix: Install XeLaTeX/LuaLaTeX on system with `texlive-luatex` and `lualatex-math` package,
   then use `fontspec` and `unicode-math` to load Georgia, Arial, Cambria Math.

2. **Column layout**: Original uses Google Docs newspaper-style two-column layout (content flows
   left column→right column naturally). Current LaTeX uses `paracol` with `\switchcolumn` for
   parallel columns. This causes different column placement for some sections.
   To fix: Could switch to `multicols` package with strategic `\columnbreak` calls, or adjust
   `\switchcolumn` placement.

3. **Column gap**: Original has ~39pt column gap; current uses 14pt. This affects the overall
   column proportions. To fix: Adjust `\columnsep` in main.tex.

4. **Margins**: Original uses ~0.5in (36pt) margins all around. Current uses 1.0in top/bottom,
   0.65in left/right. To fix: Adjust geometry in main.tex.

5. **Page size**: Original: 596×842pt (A4 exact). Current matches via `papersize={596pt,842pt}`. ✓

6. **Line spacing**: Uses `\linespread{1.15}` to approximate Google Docs default spacing.
   May need fine-tuning.

## Resolved Issues

1. **Page count mismatch**: Original 23 pages; was 22 pages. Fixed via `\linespread{1.15}`.
2. **Overfull hboxes**: Fixed line breaks in GCD properties, Segment Area text, and
   Minimum Lexicographic Rotation heading.
3. **Custom cmp pbds column**: Was in left column; original has it in right column. Fixed by
   adding `\switchcolumn` before the section.
4. **Modular architecture**: Monolithic 2971-line .tex file split into 12 modular section files.
