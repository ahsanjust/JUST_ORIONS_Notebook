# Stress Test Log

Each entry: **Section file** — subsections tested, variant compile flags passed/failed, range of random tests, result.

---

| Date | Section | Subsections | Variants | Tests | Result |
|------|---------|-------------|----------|-------|--------|
| 2026-07-22 | `01_setup_and_basics.tex` | Basic Setup (RNG/Random), Fast I/O (`readInt`, `gc`), `rd` lambda | `-O2`, `-O0 -fsanitize=address,undefined`, `#define int long long` | 2000-5000 each | ✅ PASS |
| 2026-07-22 | `02_math.tex` | Matrix Exponentiation (fib, expo, mul), XOR Basis, Gaussian Elimination, NTT | same 3 variants | 2000-5000 each | ✅ PASS |
| 2026-07-22 | `03_number_theory.tex` | Montgomery, Pollard Rho | `-O2` (debug trace) | manual trace | ❌ 3 bugs found (#3, #4, #5) |
| 2026-07-22 | `05_data_structure.tex` | Sparse2D (RMQ), Binary Trie | same 3 variants | 2000-5000 each | ✅ PASS |
| 2026-07-22 | `02_math.tex` | FFT, FWHT, Berlekamp-Massey | `-O2`, `-O0 -fsanitize=address,undefined`, `#define int long long` | 2000-5000 each | ✅ FWHT/BM PASS; ❌ FFT empty-guard missing (#7) |
| 2026-07-22 | `03_number_theory.tex` | EGCD/CRT, SPF, Segmented Sieve, Phi | `-O2`, `-O0 -fsanitize=address,undefined`, `#define int long long` | 2000-5000 each | ✅ SPF/Phi/EGCD PASS; ❌ SegSieve L=0 (#9); 🟡 EGCD sign (#8) |
| 2026-07-23 | `04_combinatorics.tex` | Burnside/Polya, Lucas Theorem, Bishop Placement | `-O2`, `-O0 -fsanitize=address,undefined` | Burnside: 2000; Lucas: 5000+500 properties; Bishop: full brute N≤4 + N=5 K∈{0,1,2,7,8,9} + formula K=2 up to N=20 | ✅ Burnside/Lucas PASS; ❌ Bishop DP geometric order bug (#10 🔴) |
| 2026-07-23 | `06_strings.tex` | Manacher, Z-Algorithm, SOS DP, Digit DP, Closest Pair of Points, Suffix Array, Aho-Corasick | `-O2`, `-O0 -fsanitize=address,undefined` | 2000-5000 each | ✅ Manacher/SOS/Digit/Closest/SA/AC PASS; ❌ Z empty-string OOB (#11 🟡) |
| 2026-07-23 | `07_graph_theory.tex` | Dinic Max Flow, Min Cost Max Flow | `-O2`, `-O0 -fsanitize=address,undefined` | 2500 small graphs + boundry | ❌ Dinic rev-index OOB (#12 🔴), s==t hang (#13 🔴); ❌ MCMF s==t hang (#14 🔴), neg-cycle hang (#15 🟡) |
| 2026-07-23 | `08_geometry.tex` | Polygon Operations (P struct, line_int, seg_int, convex hull, polygon_area, point-in-polygon, project, reflect) | `-O2`, `-O0 -fsanitize=address,undefined` | 2000 random each | ❌ line_int sign bug (#16 🔴); ❌ polygon_area truncation (#17 🟡) |
| 2026-07-23 | `07_graph_theory.tex` | Floyd-Warshall, Bellman-Ford/SPFA, Kosaraju SCC | `-O2`, `-O0 -fsanitize=address,undefined` | 2000 each | ✅ ALL PASS |
| 2026-07-23 | `08_geometry.tex` | Half-Plane Intersection | `-O2`, `-O0 -fsanitize=address,undefined` | 365+361 tests | ❌ ok() arg swap (#18 |
| 2026-07-23 | `09_dynamic_programming.tex` | Knuth Optimization, Li Chao Tree | `-O2`, `-O0 -fsanitize=address,undefined` | 2000 each | ❌ Knuth uninitialized DP (#19 🔴); ❌ Li Chao midpoint inf loop (#20 🟡) |
| 2026-07-23 | `06_strings.tex` | Double Hash, Dynamic Hash, LPS/SPS, Booth's, Eertree | `-O2`, `-O0 -fsanitize=address,undefined` | 2000 each | ✅ ALL PASS |
| 2026-07-23 | `10_others.tex` | Sprague-Grundy | `-O2`, `-O0 -fsanitize=address,undefined` | 2012 tests | ✅ PASS |
| 2026-07-23 | `06_strings.tex` | Double Hash, Dynamic Hash, LPS/SPS, Booth's, Eertree | `-O2`, `-O0 -fsanitize=address,undefined` | 2000 each | ✅ ALL PASS |
| 2026-07-23 | `07_graph_theory.tex` | 2-SAT, Hopcroft-Karp, HLD, Articulation&Bridges, BCC&Bridge Tree, Eulerian Path, Binary Lifting, Centroid, DSU-on-tree, LCT, Kruskal, Euler Tour | `-O2`, `-O0 -fsanitize=address,undefined` | 2000 each | ✅ ALL PASS |
| 2026-07-23 | `09_dynamic_programming.tex` | Max Rect Sum, Subset Sum (Bitset), Rerooting DP | `-O2`, `-O0 -fsanitize=address,undefined` | 2000 each | ✅ ALL PASS |
| 2026-07-23 | `08_geometry.tex` | Half-Plane Intersection | `-O2`, `-O0 -fsanitize=address,undefined` | 365+361 tests | ❌ ok() arg swap (#18 🟡) |
| 2026-07-23 | `09_dynamic_programming.tex` | Knuth Optimization, Li Chao Tree | `-O2`, `-O0 -fsanitize=address,undefined` | 2000 each | ❌ Knuth uninitialized DP (#19 🔴); ❌ Li Chao midpoint inf loop (#20 🟡) |
| 2026-07-23 | `10_others.tex` | Number of Digits up to N | `-O2`, `-O0 -fsanitize=address,undefined` | 2000 | ❌ int64 overflow (#21 🟡) |
| 2026-07-23 | `10_others.tex` | Bit Hacks, Sum of Digits | `-O2`, `-O0 -fsanitize=address,undefined` | 2000+ | ✅ ALL PASS |
| 2026-07-23 | `08_geometry.tex` | Area by Three Circles | `-O2`, `-O0 -fsanitize=address,undefined` | 2042 | ✅ PASS |
| 2026-07-23 | `07_graph_theory.tex` | Kruskal, Euler Tour | `-O2`, `-O0 -fsanitize=address,undefined` | 2706+165770 | ✅ PASS |
| 2026-07-23 | `06_strings.tex` | Double Hash (DHash) | `-O2`, `-O0 -fsanitize=address,undefined`, `#define int long long` | 2000 each | ✅ ALL PASS |
| 2026-07-23 | `06_strings.tex` | Periods, KMP Automaton, Lyndon Factorization | `-O2`, `-O0 -fsanitize=address,undefined` | 2000 each | ✅ ALL PASS |
| 2026-07-23 | `10_others.tex` | Sum of Digits up to N, Number of Digits up to N | `-O2`, `-O0 -fsanitize=address,undefined` | 2000 each | ✅ ALL PASS |
| 2026-07-23 | `08_geometry.tex` | Rectangle Distance, Area Enclosed by Three Circles | `-O2`, `-O0 -fsanitize=address,undefined` | 2000 each | ✅ ALL PASS |
| 2026-07-23 | `07_graph_theory.tex` | Kruskal's MST, Euler Tour, Binary Lifting (LCA), Max Rectangular Sum in Matrix, Rerooting DP, Articulation Points, Precision Handling (EEP), Bit Hacks | `-O2`, `-O0 -fsanitize=address,undefined` | 2000 each | ✅ ALL PASS |
| 2026-07-23 | `04_combinatorics.tex` | Derangements | `-O2`, `-O0 -fsanitize=address,undefined` | 201 (n=0..200) | ✅ PASS |
| 2026-07-23 | `05_data_structure.tex` | DSU | `-O2`, `-O0 -fsanitize=address,undefined` | 3000 random | ✅ PASS |
| 2026-07-23 | `05_data_structure.tex` | PBDS | `-O2`, `-O0 -fsanitize=address,undefined` | 2000 random | ✅ PASS |
| 2026-07-23 | `05_data_structure.tex` | GP Hash Table | `-O2`, `-O0 -fsanitize=address,undefined` | 2000 random | ✅ PASS |
| 2026-07-23 | `05_data_structure.tex` | Rope (GNU) | `-O2`, `-O0 -fsanitize=address,undefined` | 2000 random | ✅ PASS |
| 2026-07-23 | `05_data_structure.tex` | Sparse Table | `-O2`, `-O0 -fsanitize=address,undefined` | 3000 random | ✅ PASS |
| 2026-07-23 | `05_data_structure.tex` | Fenwick Tree (BIT) | `-O2`, `-O0 -fsanitize=address,undefined` | 3000 random | ✅ PASS |
| 2026-07-23 | `05_data_structure.tex` | Fenwick 2D | `-O2`, `-O0 -fsanitize=address,undefined` | 2000 random | ✅ PASS |
| 2026-07-23 | `05_data_structure.tex` | BIT Range Update & Range Query | `-O2`, `-O0 -fsanitize=address,undefined` | 3000 random | ✅ PASS |
| 2026-07-23 | `05_data_structure.tex` | Lazy Segment Tree | `-O2`, `-O0 -fsanitize=address,undefined` | 1000 random | ✅ PASS |
| 2026-07-23 | `05_data_structure.tex` | Persistent Segment Tree | `-O2`, `-O0 -fsanitize=address,undefined` | 1000 random | ✅ PASS |
| 2026-07-23 | `05_data_structure.tex` | Merge Sort Tree | `-O2`, `-O0 -fsanitize=address,undefined` | 2000 random | ✅ PASS |
| 2026-07-23 | `05_data_structure.tex` | Implicit Treap | `-O2`, `-O0 -fsanitize=address,undefined` | 500 random | ✅ PASS |
| 2026-07-23 | `05_data_structure.tex` | Wavelet Tree | `-O2`, `-O0 -fsanitize=address,undefined` | 500 random | ✅ PASS |
| 2026-07-23 | `05_data_structure.tex` | Mo's Algorithm | `-O2`, `-O0 -fsanitize=address,undefined` | 1000 random | ✅ PASS |
| 2026-07-23 | `05_data_structure.tex` | Rollback DSU | `-O2`, `-O0 -fsanitize=address,undefined` | 2000 random | ✅ PASS |
| 2026-07-23 | `05_data_structure.tex` | Disjoint Sparse Table | `-O2`, `-O0 -fsanitize=address,undefined` | 3000 random | ✅ PASS |
| 2026-07-23 | `05_data_structure.tex` | Min Queue | `-O2`, `-O0 -fsanitize=address,undefined` | 3000 random | ✅ PASS |
| 2026-07-23 | `05_data_structure.tex` | Small-to-Large Merging | `-O2`, `-O0 -fsanitize=address,undefined` | 500 random | ✅ PASS |
