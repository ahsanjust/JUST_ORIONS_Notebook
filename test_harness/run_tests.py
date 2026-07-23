#!/usr/bin/env python3
"""
Comprehensive test runner for C++ snippets from notebook/sections/*.tex
"""

import os
import re
import json
import subprocess
import tempfile
import sys
from datetime import datetime

SECTIONS_DIR = "/home/ahsan/Documents/cp/Template/notebook/sections"
TEST_DIR = "/tmp/stress_test"
MACROS_FILE = "/home/ahsan/Documents/cp/Template/test_harness/common_macros.h"

os.makedirs(TEST_DIR, exist_ok=True)

# Already tested sections from log
TESTED_SECTIONS = {
    '01_setup_and_basics.tex',
    '02_math.tex',
    '03_number_theory.tex',
    '04_combinatorics.tex',
    '05_data_structure.tex',
}

# Snippets already tested (from log)
ALREADY_TESTED = {
    '06_strings.tex': [3, 4],  # Z-Algorithm (index 3), Manacher (index 4)
    '08_geometry.tex': [1],     # Closest Pair (index 1)
    '09_dynamic_programming.tex': [0, 1],  # SOS DP (0), Digit DP (1)
}

# Sections to test
SECTIONS_TO_TEST = [
    '06_strings.tex',
    '07_graph_theory.tex',
    '08_geometry.tex',
    '09_dynamic_programming.tex',
    '10_others.tex',
]

def extract_snippets(tex_file):
    """Extract all minted c++ blocks from a .tex file"""
    with open(tex_file, 'r') as f:
        content = f.read()
    
    pattern = r'\\begin\{minted\}\{c\+\+\}(.*?)\\end\{minted\}'
    matches = re.findall(pattern, content, re.DOTALL)
    
    snippets = []
    for i, match in enumerate(matches):
        code = match.strip('\n').strip()
        snippets.append({
            'index': i,
            'code': code,
            'file': os.path.basename(tex_file)
        })
    return snippets

def generate_test_harness(snippet, test_name):
    """Generate a test harness for a snippet"""
    # This is a template - each snippet needs custom tests
    # We'll create a basic framework and then customize per snippet
    pass

def compile_and_run(test_file, variant):
    """Compile and run a test file with given variant"""
    base = test_file.replace('.cpp', '')
    if variant == 'O2':
        exe = f"{base}_O2"
        cmd = f"g++ -std=c++17 -O2 -I/home/ahsan/Documents/cp/Template/test_harness {test_file} -o {exe}"
    elif variant == 'asan':
        exe = f"{base}_asan"
        cmd = f"g++ -std=c++17 -O0 -fsanitize=address,undefined -I/home/ahsan/Documents/cp/Template/test_harness {test_file} -o {exe}"
    elif variant == 'll':
        exe = f"{base}_ll"
        cmd = f"g++ -std=c++17 -O0 -fsanitize=address,undefined {test_file} -o {exe}"
    else:
        raise ValueError(f"Unknown variant: {variant}")
    
    # Compile
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True, timeout=60)
    if result.returncode != 0:
        return {'success': False, 'stage': 'compile', 'error': result.stderr}
    
    # Run
    run_result = subprocess.run(exe, shell=True, capture_output=True, text=True, timeout=120)
    return {
        'success': run_result.returncode == 0,
        'stage': 'run',
        'stdout': run_result.stdout,
        'stderr': run_result.stderr,
        'returncode': run_result.returncode
    }

def main():
    print("=== Stress Test Runner ===")
    print(f"Test directory: {TEST_DIR}")
    print()
    
    all_snippets = []
    for section in SECTIONS_TO_TEST:
        path = os.path.join(SECTIONS_DIR, section)
        snippets = extract_snippets(path)
        print(f"{section}: {len(snippets)} snippets")
        
        for s in snippets:
            s['section'] = section
            # Skip already tested
            if section in ALREADY_TESTED and s['index'] in ALREADY_TESTED[section]:
                print(f"  [{s['index']}] SKIPPED (already tested)")
                continue
            all_snippets.append(s)
    
    print(f"\nTotal snippets to test: {len(all_snippets)}")
    
    # For now, let's just list them and we'll create tests manually
    for s in all_snippets:
        print(f"  {s['section']}[{s['index']}]: {s['code'][:80]}...")

if __name__ == "__main__":
    main()