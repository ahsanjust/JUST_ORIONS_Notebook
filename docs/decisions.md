# Design Decisions

## Decision Log

| Date | Decision | Rationale |
|------|----------|-----------|
| 2026-06-26 | Use modular architecture with sections/ directory | Enables parallel workflow, cleaner diffs |
| 2026-06-26 | Use `multicols*` 3-column landscape layout | Maximizes content density per page |
| 2026-06-26 | Use minted for syntax highlighting | Beautiful colored code in PDF |
| 2026-06-26 | Add `\linespread{1.15}` | Improves readability without sacrificing space |
| 2026-06-26 | Split monolithic `.tex` into 11 modular sections | Each section = one logical topic group |
| 2026-06-26 | Remove 40 redundant section files | Only 11 active files needed |
| 2026-06-26 | Exclude build artifacts via `.gitignore` | Prevents clutter in repo |
| 2026-06-29 | Rename `code_library/` → `library/` | Shorter, cleaner submodule name |
| 2026-06-29 | Rename `agent_docs/` → `docs/` | Standard project documentation directory |
| 2026-06-29 | Rename `handover.md` → `context.md`, `shared_style.md` → `style-guide.md` | More descriptive filenames |
| 2026-06-29 | Add `Makefile` + `README.md` at root | Professional entry point, `make build/view/clean` |

## Pending Decisions

1. **Font upgrade to XeLaTeX** — Would enable exact Georgia/Arial/Cambria Math matching.
   Requires `texlive-xetex` and `fontspec` package.
2. **Column model** — Consider `multicols` vs `paracol` for better match to original.
3. **Margin alignment** — Original: `0.5in`; current: `0.2in left/right`.
4. **Content additions** — What algorithms to add in the remaining ~4 pages?
