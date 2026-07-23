long double r1, r2, r3;
cin >> r1 >> r2 >> r3;
long double a = r2 + r3;
long double b = r3 + r1;
long double c = r1 + r2;
long double s = (a + b + c) / 2.0L;
long double val = s * (s - a) * (s - b) * (s - c);
long double T = val > 0 ? sqrtl(val) : 0;
auto angle = [&](long double opp, long double x, long double y) {
  long double cosv = (x * x + y * y - opp * opp) / (2.0L * x * y);
  cosv = min((long double)1.0, max((long double)-1.0, cosv));
  return acosl(cosv);
};
long double A = angle(a, b, c);
long double B = angle(b, c, a);
long double C = angle(c, a, b);
long double sectorSum = 0.5L * (r1 * r1 * A + r2 * r2 * B + r3 * r3 * C);
long double blackArea = T - sectorSum;
cout << fixed << setprecision(6) << (double)blackArea << "\n";
