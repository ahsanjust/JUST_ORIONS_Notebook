template <typename T = int, int LG = 31>
struct Basis {
  T basis[LG];
  int sz;
  vector<int> who;
  Basis() { reset(); }
  void reset() {
    fill(basis, basis + LG, 0);
    sz = 0;
    who.clear();
  }
  bool insert(T mask, int idx = -1) {
    for (int i = LG - 1; i >= 0; --i) {
      if (mask >> i & 1) {
        if (basis[i]) mask ^= basis[i];
        else {
          basis[i] = mask;
          ++sz;
          who.push_back(idx);
          return true;
        }
      }
    }
    return false;
  }
  T maxXor() {
    T ans = 0;
    for (int i = LG - 1; i >= 0; --i) ans = max(ans, ans ^ basis[i]);
    return ans;
  }
  bool can(T x) {
    for (int i = LG - 1; i >= 0; --i) {
      if (x >> i & 1) {
        if (!basis[i]) return false;
        x ^= basis[i];
      }
    }
    return true;
  }
  T kth(T k) {
    if (k < 1 || (uint64_t)k > (1ULL << sz)) return -1;
    T mask = 0;
    int64_t tot = 1LL << sz;
    for (int i = LG - 1; i >= 0; --i) {
      if (basis[i]) {
        int64_t low = tot / 2;
        if ((low < k && (~mask >> i & 1)) || (low >= k && (mask >> i & 1))) mask ^= basis[i];
        if (low < k) k -= low;
        tot /= 2;
      }
    }
    return mask;
  }
  T count_less(T x) {
    if (x < 0) return 0;
    T ret = 0, mask = 0;
    uint64_t cnt = 1ULL << sz;
    for (int i = LG - 1; i >= 0; i--) {
      if (basis[i]) {
        if (x >> i & 1) {
          ret += (cnt >> 1);
          if (~mask >> i & 1) mask ^= basis[i];
        } else {
          if (mask >> i & 1) mask ^= basis[i];
        }
        cnt >>= 1;
      } else {
        if ((x ^ mask) >> i & 1) {
          if (x >> i & 1) return ret + cnt;
          else return ret;
        }
      }
    }
    return ret;
  }
  T count_leq(T x) { return count_less(x) + (can(x) ? 1 : 0); }
  T jumpK(T val, T k) { return kth(count_leq(val) + k); }
};
