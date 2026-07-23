#pragma once
#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)(x).size()
using ll = long long;
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define eb emplace_back

const ll MOD = 1000000007;
const ll MOD2 = 998244353;

ll modpow(ll a, ll e, ll m = MOD) {
    ll r = 1;
    while (e) {
        if (e & 1) r = r * a % m;
        a = a * a % m;
        e >>= 1;
    }
    return r;
}
ll modinv(ll a, ll m = MOD) { return modpow(a, m - 2, m); }

template<typename T>
T rand_range(T lo, T hi) {
    static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    if (lo > hi) return lo;
    uniform_int_distribution<T> dist(lo, hi);
    return dist(rng);
}

template<typename T>
T rand_double(double lo, double hi) {
    static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_real_distribution<double> dist(lo, hi);
    return dist(rng);
}