ld r1, r2, r3; cin >> r1 >> r2 >> r3;
ld a = r2 + r3, b = r3 + r1, c = r1 + r2;
ld s = (a + b + c) / 2.0L;
ld val = s * (s - a) * (s - b) * (s - c);
ld T = val > 0 ? sqrtl(val) : 0;
auto angle = [&](ld opp, ld x, ld y) {
  ld cosv = (x * x + y * y - opp * opp) / (2.0L * x * y);
  return acosl(min((ld)1.0, max((ld)-1.0, cosv)));
};
ld A = angle(a, b, c), B = angle(b, c, a);
ld C = angle(c, a, b);
ld sectorSum = 0.5L * (r1 * r1 * A + r2 * r2 * B + r3 * r3 * C);
ld blackArea = T - sectorSum;
cout << fixed << setprecision(6) << (double)blackArea << "\n";
