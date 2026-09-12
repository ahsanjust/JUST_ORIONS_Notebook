// In main.cpp:
#ifndef ONLINE_JUDGE
#include "trace.cpp"
#else
#define dbg(...)
#endif

// ---- paste below into trace.cpp ----
#ifndef ONLINE_JUDGE
#define dbg(...) cerr << __LINE__ << ": ", __dbg(#__VA_ARGS__, __VA_ARGS__), cerr << "\n"

// primitive types (int,ll,char,string,etc.)
template <class T>
void __p(T x) {
  cerr << x;
}
// pair<T1,T2>
template <class T, class U>
void __p(pair<T, U> x) {
  cerr << "(" << x.first << "," << x.second << ")";
}
// vector<T>
template <class T>
void __p(vector<T> x) {
  cerr << "{";
  int _ = 0;
  for (auto y : x) {
    if (_++) cerr << ",";
    __p(y);
  }
  cerr << "}";
}
// set<T>
template <class T>
void __p(set<T> x) {
  cerr << "{";
  int _ = 0;
  for (auto y : x) {
    if (_++) cerr << ",";
    __p(y);
  }
  cerr << "}";
}
// map<K,V>
template <class T, class U>
void __p(map<T, U> x) {
  cerr << "{";
  int _ = 0;
  for (auto [k, v] : x) {
    if (_++) cerr << ",";
    __p(k);
    cerr << ":";
    __p(v);
  }
  cerr << "}";
}
// stack<T>
template <class T>
void __p(stack<T> s) {
  vector<T> v;
  while (v.size() || s.size()) v.push_back(s.top()), s.pop();
  reverse(v.begin(), v.end());
  __p(v);
}
// queue<T>
template <class T>
void __p(queue<T> q) {
  vector<T> v;
  while (q.size()) v.push_back(q.front()), q.pop();
  __p(v);
}
// priority_queue<T>
template <class T>
void __p(priority_queue<T> q) {
  vector<T> v;
  while (q.size()) v.push_back(q.top()), q.pop();
  __p(v);
}

void __dbg(const char*) {}
template <class T, class... U>
void __dbg(const char* s, T x, U... t) {
  int i = 0;
  while (s[i] && s[i] != ',') i++;
  cerr.write(s, i) << "=";
  __p(x);
  if constexpr (sizeof...(t)) cerr << " || ", __dbg(s + i + 1, t...);
}
#else
#define dbg(...)
#endif
