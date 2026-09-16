# ============================================================
# JUST_ORIONS — Notebook Build System
# ============================================================

NOTEBOOK_DIR := notebook
MAIN         := main
PDF          := $(NOTEBOOK_DIR)/$(MAIN).pdf
LATEX        := pdflatex -shell-escape -interaction=nonstopmode

# OS Detection
ifeq ($(OS),Windows_NT)
    NULL_DEV  := nul
    VIEW_CMD  := cmd /c start "" $(PDF)
    CLEAN_CMD := cmd /c "cd $(NOTEBOOK_DIR) && del /q /f *.aux *.log *.out *.toc *.fls *.fdb_latexmk *.pyg 2>nul & if exist _minted-$(MAIN) rmdir /s /q _minted-$(MAIN) & exit 0"
else
    NULL_DEV  := /dev/null
    VIEW_CMD  := xdg-open $(PDF) 2>/dev/null || open $(PDF) 2>/dev/null || echo "→ Open $(PDF) manually"
    CLEAN_CMD := cd $(NOTEBOOK_DIR) && rm -f *.aux *.log *.out *.toc *.fls *.fdb_latexmk *.pyg && rm -rf _minted-$(MAIN)/
endif

.PHONY: all build clean view help

## Default target
all: build

## Build the PDF (double-pass for correct TOC page numbers)
build:
	@echo "Building notebook (pass 1/2)..."
	@cd $(NOTEBOOK_DIR) && $(LATEX) $(MAIN).tex > $(NULL_DEV)
	@echo "Building notebook (pass 2/2)..."
	@cd $(NOTEBOOK_DIR) && $(LATEX) $(MAIN).tex > $(NULL_DEV)
	@echo "Built: $(PDF)"

## Open the PDF after building
view: build
	@$(VIEW_CMD)

## Remove all LaTeX build artifacts (keeps PDF and source)
clean:
	@echo "Cleaning build artifacts..."
	-@$(CLEAN_CMD)
	@echo "Clean"

## Show this help
help:
	@echo ""
	@echo "  JUST_ORIONS Notebook — Build Commands"
	@echo "  ─────────────────────────────────────"
	@echo "  make          Build the PDF"
	@echo "  make view     Build + open the PDF"
	@echo "  make clean    Remove build artifacts"
	@echo "  make help     Show this message"
	@echo ""
	@echo "  Requirements: TeX Live / MiKTeX, Python Pygments"
	@echo ""