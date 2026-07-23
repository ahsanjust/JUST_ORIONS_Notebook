#!/usr/bin/env python3
"""
Generate comprehensive test harnesses for all untested snippets.
"""

import os
import re
import subprocess
from pathlib import Path

SECTIONS_DIR = Path("/home/ahsan/Documents/cp/Template/notebook/sections")
TEST_DIR = Path("/tmp/stress_test")
MACROS_FILE = Path("/home/ahsan/Documents/cp/Template/test_harness/common_macros.h")

TEST_DIR.mkdir(exist_ok=True)

# Read common macros
with open(MACROS_FILE) as f:
    COMMON_MACROS = f.read()

# Template for test file
TEST_TEMPLATE = '''#include <bits/stdc++.h>
using namespace std;

{macros}

// ============ SNIPPET CODE ============
{snippet_code}

// ============ TEST HARNESS ============
{test_code}

int main() {{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    {test_calls}
    
    cerr << "ALL TESTS PASSED\\n";
    return 0;
}}
'''

def write_test_file(section, idx, snippet_code, test_code, test_calls):
    """Write a test file for a snippet."""
    name = f"stress_{section.replace('.tex', '').replace('_', '')}_{idx}"
    filepath = TEST_DIR / f"{name}.cpp"
    
    content = TEST_TEMPLATE.format(
        macros=COMMON_MACROS,
        snippet_code=snippet_code,
        test_code=test_code,
        test_calls=test_calls
    )
    
    filepath.write_text(content)
    return filepath

def compile_and_run(filepath, variant):
    """Compile and run a test file."""
    name = filepath.stem
    exe = TEST_DIR / f"{name}_{variant}"
    
    if variant == "O2":
        cmd = f"g++ -std=c++17 -O2 -I{TEST_DIR.parent}/test_harness {filepath} -o {exe}"
    elif variant == "asan":
        cmd = f"g++ -std=c++17 -O0 -fsanitize=address,undefined -I{TEST_DIR.parent}/test_harness {filepath} -o {exe}"
    elif variant == "ll":
        # For int=long long, we need to wrap the snippet only
        # This requires a separate file - skip for now, use separate file
        return True, "SKIPPED (needs separate file)"
    else:
        return False, f"Unknown variant: {variant}"
    
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True, timeout=60)
    if result.returncode != 0:
        return False, f"Compile error: {result.stderr[:500]}"
    
    run_result = subprocess.run(str(exe), shell=True, capture_output=True, text=True, timeout=120)
    if run_result.returncode != 0:
        return False, f"Runtime error: {run_result.stderr[:500]}"
    
    return True, run_result.stdout.strip()

# ============================================================
# TEST CODE FOR EACH SNIPPET
# ============================================================

# --- 06_strings.tex ---

TEST_06_0_DHASH = '''
// Brute force oracle for DHash
pair<ll,ll> brute_get(const string& s, int l, int r, ll mod, ll base) {
    ll h = 0;
    for (int i = l; i <= r; i++) {
        h = (h * base + s[i]) % mod;
    }
    return {h, h};
}

pair<ll,ll> brute_get2(const string& s, int l, int r) {
    auto h1 = brute_get(s, l, r, 1000000007LL, 911382323LL);
    auto h2 = brute_get(s, l, r, 1000000009LL, 972663749LL);
    return {h1.first, h2.first};
}

bool test_dhash() {
    mt19937 rng(12345);
    uniform_int_distribution<int> len_dist(0, 100);
    uniform_int_distribution<int> char_dist('a', 'z');
    
    for (int tc = 0; tc < 2000; tc++) {
        int n = len_dist(rng);
        string s;
        for (int i = 0; i < n; i++) s += char(char_dist(rng));
        
        DHash dh(s);
        
        for (int l = 0; l < n; l++) {
            for (int r = l; r < n; r++) {
                auto expected = brute_get2(s, l, r);
                auto actual = dh.get(l, r);
                if (expected != actual) {
                    cerr << "FAIL: DHash mismatch\\n";
                    cerr << "  s=" << s << " l=" << l << " r=" << r << "\\n";
                    cerr << "  expected=(" << expected.first << "," << expected.second << ")\\n";
                    cerr << "  actual=(" << actual.first << "," << actual.second << ")\\n";
                    return false;
                }
            }
        }
    }
    
    // Edge cases
    DHash empty("");
    DHash single("a");
    assert(single.get(0,0).first == 'a' % 1000000007LL);
    
    // Adversarial
    vector<string> adv = {"", "a", "aa", "aaa", "ab", "aba", "abab", string(100,'a')};
    for (auto& s : adv) {
        DHash dh(s);
        for (int l = 0; l < (int)s.size(); l++) {
            for (int r = l; r < (int)s.size(); r++) {
                auto expected = brute_get2(s, l, r);
                auto actual = dh.get(l, r);
                if (expected != actual) return false;
            }
        }
    }
    
    cerr << "DHash: PASS\\n";
    return true;
}
'''

CALL_06_0 = 'if (!test_dhash()) return 1;'

# ... This is getting very large. Let me create a more efficient approach.
# I'll write individual test files for each snippet instead.

print("Test generator ready - need to write specific tests for each snippet")