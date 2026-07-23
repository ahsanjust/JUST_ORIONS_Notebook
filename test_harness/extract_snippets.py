#!/usr/bin/env python3
"""
Extract C++ snippets from notebook/sections/*.tex files
and generate test harnesses for stress testing.
"""

import re
import os
import sys
import subprocess
import tempfile
import hashlib
import json

SECTIONS_DIR = "/home/ahsan/Documents/cp/Template/notebook/sections"
TEST_DIR = "/tmp/stress_test"
MACROS_FILE = "/home/ahsan/Documents/cp/Template/test_harness/common_macros.h"

os.makedirs(TEST_DIR, exist_ok=True)

def extract_snippets(tex_file):
    """Extract all minted c++ blocks from a .tex file."""
    with open(tex_file, 'r') as f:
        content = f.read()
    
    # Pattern to match \begin{minted}{c++} ... \end{minted}
    pattern = r'\\begin\{minted\}\{c\+\+\}(.*?)\\end\{minted\}'
    matches = re.findall(pattern, content, re.DOTALL)
    
    snippets = []
    for i, match in enumerate(matches):
        # Clean up the code
        code = match.strip()
        # Remove leading/trailing newlines
        code = code.strip('\n')
        snippets.append({
            'index': i,
            'code': code,
            'file': os.path.basename(tex_file)
        })
    return snippets

def generate_test_name(file_name, idx):
    """Generate a unique test name."""
    base = file_name.replace('.tex', '').replace('_', '')
    return f"stress_{base}_{idx}"

def compile_and_run(test_name, cpp_code, extra_flags=""):
    """Compile and run a C++ test with given flags."""
    test_file = os.path.join(TEST_DIR, f"{test_name}.cpp")
    exe_file = os.path.join(TEST_DIR, f"{test_name}")
    
    with open(test_file, 'w') as f:
        f.write(cpp_code)
    
    # Three compilation variants
    variants = [
        f"g++ -std=c++17 -O2 -I/home/ahsan/Documents/cp/Template/test_harness {test_file} -o {exe_file}_O2",
        f"g++ -std=c++17 -O0 -fsanitize=address,undefined -I/home/ahsan/Documents/cp/Template/test_harness {test_file} -o {exe_file}_asan",
        f"g++ -std=c++17 -O0 -fsanitize=address,undefined -Dint=long long -I/home/ahsan/Documents/cp/Template/test_harness {test_file} -o {exe_file}_ll"
    ]
    
    results = []
    for i, cmd in enumerate(variants):
        try:
            result = subprocess.run(cmd, shell=True, capture_output=True, text=True, timeout=30)
            if result.returncode != 0:
                results.append({
                    'variant': i,
                    'success': False,
                    'error': result.stderr,
                    'output': result.stdout
                })
            else:
                # Run the executable
                run_cmd = f"{exe_file}_{['O2', 'asan', 'll'][i]}"
                run_result = subprocess.run(run_cmd, shell=True, capture_output=True, text=True, timeout=60)
                results.append({
                    'variant': i,
                    'success': run_result.returncode == 0,
                    'error': run_result.stderr,
                    'output': run_result.stdout
                })
        except subprocess.TimeoutExpired:
            results.append({
                'variant': i,
                'success': False,
                'error': 'TIMEOUT',
                'output': ''
            })
        except Exception as e:
            results.append({
                'variant': i,
                'success': False,
                'error': str(e),
                'output': ''
            })
    
    return results

def test_snippet(snippet, test_name):
    """Test a single snippet with a basic harness."""
    # This is a placeholder - each snippet needs a custom test
    pass

def main():
    # Test extraction on all untested sections
    untested = [
        '06_strings.tex',
        '07_graph_theory.tex', 
        '08_geometry.tex',
        '09_dynamic_programming.tex',
        '10_others.tex'
    ]
    
    all_snippets = []
    for section in untested:
        path = os.path.join(SECTIONS_DIR, section)
        snippets = extract_snippets(path)
        print(f"{section}: {len(snippets)} snippets")
        for s in snippets:
            s['section'] = section
        all_snippets.extend(snippets)
    
    print(f"Total snippets to test: {len(all_snippets)}")
    
    # Save snippet info for reference
    with open(os.path.join(TEST_DIR, 'snippets.json'), 'w') as f:
        json.dump(all_snippets, f, indent=2)
    
    return all_snippets

if __name__ == "__main__":
    main()