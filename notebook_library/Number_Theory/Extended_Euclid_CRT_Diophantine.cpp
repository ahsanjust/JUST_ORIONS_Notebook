#include <bits/stdc++.h>
using namespace std;

using ll = long long;

namespace LDE {
using i128 = __int128_t;

// in: a, b, &x, &y | out: g=gcd>=0, a*x+b*y=g
ll extgcd(ll a, ll b, ll& x, ll& y) {
  if (!b) return x = (a < 0 ? -1 : 1), y = 0, abs(a);
  ll g = extgcd(b, a % b, y, x);
  return y -= a / b * x, g;
}

// in: a, m | out: inv in [0,m-1] s.t. (a*x)%m=1
// returns -1 if gcd(a,m) != 1 or m <= 1
ll mod_inv(ll a, ll m) {
  if (m <= 1) return -1;
  ll x, y, g = extgcd((a % m + m) % m, m, x, y);
  return g == 1 ? (x % m + m) % m : -1;
}

// Solves: a*x = b (mod m)
// in: a, b, m
// out: {x0, step} => x = x0 (mod step).
// Sols in [0,m-1]: x0 + k*step (total m/step).
// Returns {-1, -1} if no sol (b % gcd != 0)
pair<ll, ll> congruence(ll a, ll b, ll m) {
  if (m <= 0) return {-1, -1};
  ll u, v, g = extgcd(a, m, u, v);
  if (b % g) return {-1, -1};
  ll st = m / g, x0 = ((i128)u * (b / g) % st + st) % st;
  return {x0, st};
}

// Solves: x = r1 (mod m1), x = r2 (mod m2)
// in: r1, m1, r2, m2 (any m1, m2 > 0)
// out: {x0, lcm} => x = x0 (mod lcm), 0<=x0<lcm
// Returns {-1, -1} if inconsistent
pair<ll, ll> crt(ll r1, ll m1, ll r2, ll m2) {
  if (m1 <= 0 || m2 <= 0) return {-1, -1};
  r1 = (r1 % m1 + m1) % m1;
  r2 = (r2 % m2 + m2) % m2;
  auto [k0, st] = congruence(m1, r2 - r1, m2);
  if (k0 == -1) return {-1, -1};
  i128 lcm = (i128)m1 * st;
  return {(r1 + (i128)k0 * m1) % lcm, (ll)lcm};
}

// in: vector r, m | out: {x0, lcm} / {-1,-1}
pair<ll, ll> crt(const vector<ll>& r, const vector<ll>& m) {
  pair<ll, ll> c = {0, 1};
  for (int i = 0; i < (int)r.size(); i++)
    if ((c = crt(c.first, c.second, r[i], m[i])).second == -1) break;
  return c;
}

// Solves: a*x + b*y = c (Linear Diophantine)
// in: a, b, c, &x, &y, &g
// out: true if sol exists (g|c), sets g, (x,y)
// Base sol: x in [0, |b/g|-1] (never overflows)
// General: x' = x+k*(b/g), y' = y-k*(a/g)
bool any_sol(ll a, ll b, ll c, ll& x, ll& y, ll& g) {
  if (!a && !b) {
    g = x = y = 0;
    return c == 0;
  }
  g = extgcd(a, b, x, y);
  if (c % g) return false;
  if (b) {
    ll m = abs(b / g);
    x = ((i128)x * (c / g) % m + m) % m;
    y = (c - (i128)a * x) / b;
  } else x = c / a, y = 0;
  return true;
}

// Precondition: b > 0
i128 flr(i128 a, i128 b) {
  return a >= 0 ? a / b : (a - b + 1) / b;
}
i128 cil(i128 a, i128 b) {
  return a >= 0 ? (a + b - 1) / b : a / b;
}

// in: u, v, L, R | out: [k_min, k_max] s.t. L <= u + k*v <= R
pair<i128, i128> range_k(i128 u, i128 v, i128 L, i128 R) {
  if (v < 0) u = -u, v = -v, swap(L, R), L = -L, R = -R;
  return {cil(L - u, v), flr(R - u, v)};
}

// in: a, b, c, box [lx,rx] x [ly,ry]
// out: [kl, kr] for parameter k. If kl > kr, no sol
pair<i128, i128> k_range(ll a, ll b, ll c, ll lx, ll rx, ll ly, ll ry, ll& x, ll& y, ll& g) {
  if (lx > rx || ly > ry || !any_sol(a, b, c, x, y, g)) return {1, 0};
  auto [k1, k2] = range_k(x, b / g, lx, rx);
  auto [k3, k4] = range_k(y, -a / g, ly, ry);
  return {max(k1, k3), min(k2, k4)};
}

// in: a*x + b*y = c and box [lx,rx] x [ly,ry]
// out: count of integer pairs (x,y) in box
ll count_sol(ll a, ll b, ll c, ll lx, ll rx, ll ly, ll ry) {
  if (lx > rx || ly > ry) return 0;
  if (!a && !b) return c ? 0 : (ll)((i128)(rx - lx + 1) * (ry - ly + 1));
  if (!a) return (c % b == 0 && ly <= c / b && c / b <= ry) ? rx - lx + 1 : 0;
  if (!b) return (c % a == 0 && lx <= c / a && c / a <= rx) ? ry - ly + 1 : 0;
  ll x, y, g;
  auto [kl, kr] = k_range(a, b, c, lx, rx, ly, ry, x, y, g);
  return kl > kr ? 0 : (ll)(kr - kl + 1);
}

// in: a*x + b*y = c and box [lx,rx] x [ly,ry]
// out: solution (x, y) with minimum x, or {-1, -1}
pair<ll, ll> min_x_sol(ll a, ll b, ll c, ll lx, ll rx, ll ly, ll ry) {
  if (lx > rx || ly > ry) return {-1, -1};
  if (!a && !b) return c == 0 ? pair{lx, ly} : pair{-1LL, -1LL};
  if (!a) return (c % b == 0 && ly <= c / b && c / b <= ry) ? pair{lx, c / b} : pair{-1LL, -1LL};
  if (!b) return (c % a == 0 && lx <= c / a && c / a <= rx) ? pair{c / a, ly} : pair{-1LL, -1LL};
  ll x, y, g;
  auto [kl, kr] = k_range(a, b, c, lx, rx, ly, ry, x, y, g);
  if (kl > kr) return {-1, -1};
  i128 k = (b / g > 0 ? kl : kr);
  return {(ll)(x + k * (b / g)), (ll)(y - k * (a / g))};
}
}  // namespace LDE
