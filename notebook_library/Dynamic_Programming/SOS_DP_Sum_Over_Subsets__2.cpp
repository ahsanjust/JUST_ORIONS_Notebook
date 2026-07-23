void Solve() {
  ll n;
  cin >> n;
  vector<ll> arr(n);
  for (auto& x : arr)
    cin >> x;
  ll N = 1 + __lg(*max_element(arr.begin(), arr.end()));
  vector<ll> sos(1LL << N, 0), sos2(1LL << N, 0);
  for (auto it : arr) {
    sos[it]++;
    sos2[((1LL << N) - 1) ^ it]++;
  }
  for (int i = 0; i < N; ++i)
    for (int mask = 0; mask < (1LL << N); ++mask)
      if (mask & (1LL << i))
        sos[mask] += sos[mask ^ (1LL << i)], sos2[mask] += sos2[mask ^ (1LL << i)];
  for (auto& it : arr) {
    // count y: x|y == x
    cout << sos[it] << ' ';
    // count y: x&y == x
    cout << sos2[((1LL << N) - 1) ^ it] << ' ';
    // count y: x&y != 0
    cout << n - sos[((1LL << N) - 1) ^ it] << ' ';
  }
}
