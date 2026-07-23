long double L, W;
if (!(cin >> L >> W))
  return 0;
long double h = sqrtl(L * L + W * W);
long double P = L + W + h;
long double x1 = L * (L + h) / P;
long double y1 = L * W / P;
long double x2 = L * W / P;
long double y2 = W * (W + h) / P;
long double dx = x1 - x2;
long double dy = y1 - y2;
long double D = sqrtl(dx * dx + dy * dy);
cout << fixed << setprecision(6) << (double)D << "\n";
