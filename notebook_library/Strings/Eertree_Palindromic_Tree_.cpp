struct Eertree {
  vector<array<int, 26>> nxt;
  vector<int> len, link, cnt;
  int last;
  Eertree(const string &s) : last(1) {
    len = {-1, 0};
    link = {0, 0};
    cnt = {0, 0};
    nxt.push_back({});
    nxt.push_back({});
    for (int i = 0; i < (int)s.size(); i++)
      add(s, i);
    for (int i = (int)len.size() - 1; i > 1; i--)
      cnt[link[i]] += cnt[i];
  }
  void add(const string &s, int i) {
    int c = s[i] - 'a', cur = last;
    while (true) {
      int cl = len[cur];
      if (i - cl - 1 >= 0 && s[i - cl - 1] == s[i])
        break;
      cur = link[cur];
    }
    if (nxt[cur][c]) {
      last = nxt[cur][c];
      cnt[last]++;
      return;
    }
    int node = len.size();
    nxt.push_back({});
    len.push_back(len[cur] + 2);
    cnt.push_back(1);
    nxt[cur][c] = node;
    if (len[node] == 1) {
      link.push_back(1);
      last = node;
      return;
    }
    int l = link[cur];
    while (true) {
      int ll = len[l];
      if (i - ll - 1 >= 0 && s[i - ll - 1] == s[i])
        break;
      l = link[l];
    }
    link.push_back(nxt[l][c]);
    last = node;
  }
};
