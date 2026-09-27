const ld EPS = 1e-9;
bool equal(ld a, ld b) { return abs(a - b) < EPS; }
bool lessThan(ld a, ld b) { return a < b - EPS; }
bool greaterThan(ld a, ld b) { return a > b + EPS; }
