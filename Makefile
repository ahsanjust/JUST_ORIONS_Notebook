# ============================================================
# JUST_ORIONS — Notebook Build System
# ============================================================

NOTEBOOK_DIR := notebook
MAIN         := main
PDF          := $(NOTEBOOK_DIR)/$(MAIN).pdf
LATEX        := pdflatex -shell-escape -interaction=nonstopmode

.PHONY: all build clean view watch help

## Default target
all: build

## Build the PDF (double-pass for correct TOC page numbers)
build:
	@echo "→ Building notebook (pass 1/2)..."
	@cd $(NOTEBOOK_DIR) && $(LATEX) $(MAIN).tex > /dev/null
	@echo "→ Building notebook (pass 2/2)..."
	@cd $(NOTEBOOK_DIR) && $(LATEX) $(MAIN).tex > /dev/null
	@echo "✓ Built: $(PDF)"

## Open the PDF after building
view: build
	@xdg-open $(PDF) 2>/dev/null || open $(PDF) 2>/dev/null || echo "→ Open $(PDF) manually"

## Remove all LaTeX build artifacts (keeps PDF and source)
clean:
	@echo "→ Cleaning build artifacts..."
	@cd $(NOTEBOOK_DIR) && rm -f *.aux *.log *.out *.toc *.fls *.fdb_latexmk *.pyg
	@rm -rf $(NOTEBOOK_DIR)/_minted-$(MAIN)/
	@echo "✓ Clean"

## Show this help
help:
	@echo ""
	@echo "  JUST_ORIONS Notebook — Build Commands"
	@echo "  ─────────────────────────────────────"
	@echo "  make         Build the PDF"
	@echo "  make view    Build + open the PDF"
	@echo "  make clean   Remove build artifacts"
	@echo "  make help    Show this message"
	@echo ""
	@echo "  Requirements: texlive-full, python3-pygments"
	@echo ""
