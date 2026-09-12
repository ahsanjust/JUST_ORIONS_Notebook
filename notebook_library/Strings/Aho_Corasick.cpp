const int N = 1e6 + 6;
int trie[N][26], fail[N], exit_link[N], is_end[N];
int ptr;
void init() {
  for (int i = 0; i <= ptr; i++) {
    fill(trie[i], trie[i] + 26, 0);
    fail[i] = exit_link[i] = is_end[i] = 0;
  }
  ptr = 1;
}
void ins(string &s) {
  int cur = 0;
  for (auto c : s) {
    int d = c - 'a';
    if (!trie[cur][d]) trie[cur][d] = ptr++;
    cur = trie[cur][d];
  }
  is_end[cur] = s.size();
}
void build_fails() {
  queue<int> q;
  for (int i = 0; i < 26; i++)
    if (trie[0][i]) q.push(trie[0][i]);
  while (q.size()) {
    int cur = q.front();
    q.pop();
    exit_link[cur] = is_end[fail[cur]] > 0 ? fail[cur] : exit_link[fail[cur]];
    for (int d = 0; d < 26; d++) {
      if (trie[cur][d]) {
        q.push(trie[cur][d]);
        fail[trie[cur][d]] = trie[fail[cur]][d];
      } else {
        trie[cur][d] = trie[fail[cur]][d];
      }
    }
  }
}
