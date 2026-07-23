using T = __int128_t;
T egcd(T a, T b, T &x, T &y) {
  T xx = y = 0, yy = x = 1;
  while (b) {
    T q = a / b;
    T t = b;
    b = a % b;
    a = t;
    t = xx;
    xx = x - q * xx;
    x = t;
    t = yy;
    yy = y - q * yy;
    y = t;
  }
  if (a < 0) {
    a = -a;
    x = -x;
    y = -y;
  }
  return a;
}
pair<T, T> crt(T a1, T m1, T a2, T m2) {
  T p, q;
  T g = egcd(m1, m2, p, q);
  if (a1 % g != a2 % g)
    return {0, -1};
  T m = m1 / g * m2;
  p = (p % m + m) % m;
  q = (q % m + m) % m;
  T x = p * a2 % m * (m1 / g) % m + q * a1 % m * (m2 / g) % m;
  return {x % m, m};
}
ll extgcd(ll a, ll b, ll &x, ll &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  ll x1, y1;
  ll d = extgcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - y1 * (a / b);
  return d;
}
bool find_any_solution(ll a, ll b, ll c, ll &x0, ll &y0, ll &g) {
  g = extgcd(abs(a), abs(b), x0, y0);
  if (c % g)
    return false;
  x0 *= c / g;
  y0 *= c / g;
  if (a < 0)
    x0 = -x0;
  if (b < 0)
    y0 = -y0;
  return true;
}
