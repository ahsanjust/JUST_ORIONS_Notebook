struct MinQueue {
  deque<int> dq;  // increasing values
  queue<int> q;   // actual elements
  void push(int x) {
    q.push(x);
    while (!dq.empty() && dq.back() > x)
      dq.pop_back();
    dq.push_back(x);
  }
  void pop() {
    if (q.front() == dq.front())
      dq.pop_front();
    q.pop();
  }
  int get_min() {
    return dq.front();
  }
  bool empty() {
    return q.empty();
  }
};
// For max: change > to < in push, rename to MaxQueue.
