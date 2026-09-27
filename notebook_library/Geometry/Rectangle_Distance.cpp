ld L, W; if (!(cin >> L >> W)) return 0;
ld h = sqrtl(L * L + W * W), P = L + W + h;
ld x1 = L * (L + h) / P, y1 = L * W / P;
ld x2 = y1, y2 = W * (W + h) / P;
ld dx = x1 - x2, dy = y1 - y2;
ld D = sqrtl(dx * dx + dy * dy);
cout << fixed << setprecision(6) << (double)D << "\n";
