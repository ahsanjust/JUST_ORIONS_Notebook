#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

// GP Hash Table: 3-6x faster drop-in for unordered_map (Robin Hood probing).
// Always pass custom_hash with SplitMix64 to prevent O(N^2) anti-hash hacking on Codeforces.
struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  size_t operator()(uint64_t x) const {
    static const uint64_t R = chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + R);
  }
  size_t operator()(pair<uint64_t, uint64_t> p) const {
    return (*this)(p.first) ^ ((*this)(p.second) << 1);
  }
};
gp_hash_table<int, int, custom_hash> mp;
// For pair keys: gp_hash_table<pair<ll, ll>, int, custom_hash> mp2;
