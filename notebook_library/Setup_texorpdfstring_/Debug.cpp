#ifndef ONLINE_JUDGE
#define dbg(...) cerr << "[" #__VA_ARGS__ "]:", pr(__VA_ARGS__)

string to_string(char c) { return string(1, c); }
string to_string(bool b) { return b ? "T" : "F"; }
string to_string(const char* s) { return s; }
string to_string(char* s) { return s; }
string to_string(string s) { return s; }

template <class A, class B>
string to_string(pair<A, B> p);

template <class A>
string to_string(A v) {
  string r = "{"; int f = 0;
  for (auto& x : v)
    r += (f++ ? "," : "") + to_string(x);
  return r + "}";
}

template <class A, class B>
string to_string(pair<A, B> p) {
  return "(" + to_string(p.first) + ","
             + to_string(p.second) + ")";
}

template <class T, class... C>
string to_string(queue<T, C...> q) {
  string r = "{"; int f = 0;
  for (; q.size(); q.pop())
    r += (f++ ? "," : "") + to_string(q.front());
  return r + "}";
}

// For stack / priority_queue: replace queue with stack / priority_queue & .front() with .top()

void pr() { cerr << "\n"; }
template <class H, class... T>
void pr(H h, T... t) {
  cerr << " " << to_string(h); pr(t...);
}
#else
#define dbg(...)
#endif
