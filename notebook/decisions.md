# Decisions Log — JUST_ORIONS Notebook

## Decision 1: Modular Architecture
- **Date:** 2026-06-26
- **Decision:** Split the single 2971-line tex file into 11 section files
- **Rationale:** Enables parallel agent work, easier maintenance, cleaner code
- **Impact:** All agents can work independently on their assigned sections

## Decision 2: Extraction Method
- **Date:** 2026-06-26
- **Decision:** Extract sections directly from original tex using sed line ranges
- **Rationale:** Guarantees exact content fidelity - no re-typing errors
- **Impact:** All content is byte-identical to the original source

## Decision 3: Column Flow Preservation
- **Date:** 2026-06-26
- **Decision:** Preserve all \switchcolumn calls within section files
- **Rationale:** The paracol column switching must maintain correct left/right alternation
- **Impact:** Each section file may contain switchcolumn calls; main.tex just inputs them in order

## Decision 4: Font Choice
- **Date:** 2026-06-26
- **Decision:** Keep Charter font for body text, Latin Modern Typewriter for code
- **Rationale:** The original PDF appears to use Charter-like fonts; switching would change appearance
- **Impact:** Visual output closely matches original; remaining differences are rendering engine artifacts

## Decision 5: Overfull hbox Acceptance
- **Date:** 2026-06-26
- **Decision:** Accept 3 minor overfull hbox warnings (same as original compilation)
- **Rationale:** These are present in the original tex compilation and fixing them would change content
- **Impact:** No visual impact at normal viewing; warnings only visible in log
