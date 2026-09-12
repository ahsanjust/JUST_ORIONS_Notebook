#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T, class Cmp = less<T>>
using OS = tree<T, null_type, Cmp, rb_tree_tag, tree_order_statistics_node_update>;

// Multiset: strictly use pair<T, int> to avoid UB!
// Insert: s.insert({val, id++})
// Erase exactly x: s.erase(s.lower_bound({x, 0}))

// find_by_order(k) -> iterator to k-th element
// order_of_key({x, 0}) -> count of elements < x

// Lower Bound of x (first element >= x):
// int idx = s.order_of_key({x, 0}); // 0-indexed
// if (idx == s.size()) no_lower_bound;
// else lb = s.find_by_order(idx)->first;

// Max element < x: s.find_by_order(idx - 1)->first
// Upper Bound of x: s.order_of_key({x + 1, 0})

// --- Custom Comparator Example ---
struct cmp {
  bool operator()(int a, int b) { return a > b; }  // must be strict
};
using custom_set = OS<int, cmp>;
