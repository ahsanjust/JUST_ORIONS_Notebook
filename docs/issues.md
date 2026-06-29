# Issues

## Current Issues

1. **Font mismatch**: Original uses Georgia (body), Arial (code), Cambria Math (math).
   Current LaTeX uses Times (mathptmx), Courier (code), Times (math).
   To fix: Install XeLaTeX/LuaLaTeX with `fontspec` and `unicode-math`.

2. **Column layout**: Original uses Google Docs newspaper-style two-column layout.
   Current uses `paracol` with `\switchcolumn`. May cause different column placement.

3. **Column gap**: Original has ~39pt column gap; current uses 14pt.
   To fix: Adjust `\columnsep` in main.tex.

4. **Margins**: Original uses ~0.5in (36pt) margins. Current uses 1.0in top/bottom,
   0.65in left/right. To fix: Adjust geometry in main.tex.

5. **Page size**: Original: 596×842pt. Current matches via `papersize={596pt,842pt}`. ✓

6. **code_library submodule**: code_library/ is tracked as a gitlink (160000) without proper
   `.gitmodules` entry. Should be fixed or converted to proper submodule.

## Resolved Issues

1. **Redundant section files**: Removed 40 duplicate/unused .tex files from sections/
2. **Build artifacts clutter**: Added *.aux *.log to .gitignore
3. **code_library directory disorganization**: Reorganized into professional structure
4. **Page count mismatch**: Fixed via `\linespread{1.15}` (now 23 pages ✓)
5. **Overfull hboxes**: Fixed line breaks in GCD properties, Segment Area text, etc.
6. **Custom cmp pbds column**: Fixed column placement.
