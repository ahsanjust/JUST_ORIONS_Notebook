#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

// ============================================================
// 1. Order Statistics Tree (Ordered Set / Map / Multiset)
// ============================================================
template <class T, class Cmp = less<T>>
using OS = tree<T, null_type, Cmp, rb_tree_tag, tree_order_statistics_node_update>;

// • find_by_order(k) -> iterator to k-th smallest element (0-indexed, 0 <= k < size)
//   Value: *s.find_by_order(k). Returns s.end() if k >= size.
// • order_of_key(x)  -> count of elements strictly < x (0-based rank / insert pos)
// • Bounds: lower_bound(x) (first >= x), upper_bound(x) (first > x)
// • Max element < x: *s.find_by_order(s.order_of_key(x) - 1)

// Map: replace null_type with ValueType (e.g., OS<int, int> mp;)
// Descending: OS<int, greater<int>> s;
// Custom Comparator (must be strict weak ordering):
struct Cmp {
  bool operator()(int a, int b) const { return a > b; }
};

// --- Ordered Multiset Idiom ---
// Avoid less_equal<T> (UB: breaks erase and lower_bound). Store pair<T, int> with unique IDs:
// OS<pair<int, int>> s; int timer = 0;
// Insert:           s.insert({x, ++timer});
// Erase 1 instance: auto it = s.lower_bound({x, 0});
//                   if (it != s.end() && it->first == x) s.erase(it);
// Rank < x:         s.order_of_key({x, 0})
// Rank <= x:        s.order_of_key({x + 1, 0})
// Count of x:       s.order_of_key({x + 1, 0}) - s.order_of_key({x, 0})

// ============================================================
// 2. GP Hash Table (Anti-Hash SplitMix64)
// ============================================================
// 3-6x faster drop-in for unordered_map (Robin Hood probing).
// Default std::hash has trivial collisions hacked to O(N^2) on Codeforces.
// Always pass custom_hash with SplitMix64 + randomized clock seed.
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
