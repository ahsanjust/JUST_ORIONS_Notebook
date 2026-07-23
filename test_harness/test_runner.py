#!/usr/bin/env python3
"""
Comprehensive stress test generator and runner for C++ snippets.
"""

import os
import re
import json
import subprocess
import tempfile
from pathlib import Path
from datetime import datetime

SECTIONS_DIR = Path("/home/ahsan/Documents/cp/Template/notebook/sections")
TEST_DIR = Path("/tmp/stress_test")
MACROS_FILE = Path("/home/ahsan/Documents/cp/Template/test_harness/common_macros.h")
LOG_FILE = Path("/home/ahsan/Documents/cp/Template/docs/STRESSTEST_LOG.md")
ISSUES_FILE = Path("/home/ahsan/Documents/cp/Template/notebook/issues.md")

TEST_DIR.mkdir(exist_ok=True)

# Untested snippets (excluding already tested ones)
UNTESTED_SNIPPETS = {
    "06_strings.tex": [0, 1, 2, 5, 6, 7, 8, 9, 10, 11],  # 10 snippets (Manacher=4, Z-algo=3 already tested)
    "07_graph_theory.tex": list(range(17)),  # 17 snippets
    "08_geometry.tex": [0, 1, 3, 4, 5],  # 5 snippets (Closest Pair=2 already tested)
    "09_dynamic_programming.tex": [2, 3, 4, 5, 6, 7],  # 6 snippets (SOS=0, Digit=1 already tested)
    "10_others.tex": list(range(4)),  # 4 snippets
}

def extract_snippets(tex_file):
    """Extract all minted c++ blocks from a .tex file."""
    content = tex_file.read_text()
    pattern = r'\\begin\{minted\}\{c\+\+\}(.*?)\\end\{minted\}'
    matches = re.findall(pattern, content, re.DOTALL)
    snippets = []
    for i, match in enumerate(matches):
        code = match.strip('\n').strip()
        snippets.append({'index': i, 'code': code})
    return snippets

def generate_test_harness(section_name, snippet_idx, snippet_code):
    """Generate a test harness for a snippet."""
    # This is a template - each snippet needs custom tests
    # For now, we'll create a basic compilation test
    pass

def compile_and_run(test_file, variant):
    """Compile and run a test file with given variant."""
    name = test_file.stem
    exe = TEST_DIR / f"{name}_{variant}"
    
    if variant == "O2":
        cmd = f"g++ -std=c++17 -O2 -I{TEST_DIR.parent}/test_harness {test_file} -o {exe}"
    elif variant == "asan":
        cmd = f"g++ -std=c++17 -O0 -fsanitize=address,undefined -I{TEST_DIR.parent}/test_harness {test_file} -o {exe}"
    elif variant == "ll":
        cmd = f"g++ -std=c++17 -O0 -fsanitize=address,undefined -Dint=long\\ long -I{TEST_DIR.parent}/test_harness {test_file} -o {exe}"
    else:
        return False, "Unknown variant"
    
    # Compile
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True, timeout=60)
    if result.returncode != 0:
        return False, f"Compile error: {result.stderr}"
    
    # Run
    run_result = subprocess.run(str(exe), shell=True, capture_output=True, text=True, timeout=120)
    if run_result.returncode != 0:
        return False, f"Runtime error: {run_result.stderr}\nOutput: {run_result.stdout}"
    
    return True, run_result.stdout

def main():
    print("Stress Test Runner")
    print("=" * 50)
    
    # First, extract all snippets to understand what we're dealing with
    all_snippets = {}
    for section_file, indices in UNTESTED_SNIPPETS.items():
        tex_path = SECTIONS_DIR / section_file
        snippets = extract_snippets(tex_path)
        all_snippets[section_file] = snippets
        print(f"{section_file}: {len(snippets)} total snippets, testing {len(indices)}")
    
    # TODO: Generate and run tests for each snippet
    print("\nTest generation not yet implemented - need custom harnesses per snippet")
    
    # Show summary of what needs testing
    print("\n=== SNIPPETS TO TEST ===")
    for section_file, indices in UNTESTED_SNIPPETS.items():
        print(f"\n{section_file}:")
        snippets = all_snippets[section_file]
        for idx in indices:
            if idx < len(snippets):
                code_preview = snippets[idx]['code'][:80].replace('\n', ' ')
                print(f"  [{idx}] {code_preview}...")

if __name__ == "__main__":
    main()