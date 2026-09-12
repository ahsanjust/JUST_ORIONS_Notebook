if (n > 0) D[1] = 0;
if (n > 1) D[2] = 1;
for (int i = 3; i <= n; i++) D[i] = (i - 1) * (D[i - 1] + D[i - 2]);
