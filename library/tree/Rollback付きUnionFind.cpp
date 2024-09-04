#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <atcoder/all>
using namespace atcoder;
using namespace boost::multiprecision;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
//constexpr ll MOD = 1000000007;
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;

struct RollbackUnionFind {
  vector<int> data;
  stack<pair<int, int> > history;
  int inner_snap;

  RollbackUnionFind(int sz) : inner_snap(0) { data.assign(sz, -1); }

  bool unite(int x, int y) {
    x = find(x), y = find(y);
    history.emplace(x, data[x]);
    history.emplace(y, data[y]);
    if (x == y) return false;
    if (data[x] > data[y]) swap(x, y);
    data[x] += data[y];
    data[y] = x;
    return true;
  }

  int find(int k) {
    if (data[k] < 0) return k;
    return find(data[k]);
  }

  int same(int x, int y) { return find(x) == find(y); }

  int size(int k) { return (-data[find(k)]); }

  void undo() {
    data[history.top().first] = history.top().second;
    history.pop();
    data[history.top().first] = history.top().second;
    history.pop();
  }

  void snapshot() { inner_snap = int(history.size() >> 1); }

  int get_state() { return int(history.size() >> 1); }

  void rollback(int state = -1) {
    if (state == -1) state = inner_snap;
    state <<= 1;
    assert(state <= (int)history.size());
    while (state < (int)history.size()) undo();
  }
};

/**
 * @brief RollbackつきUnion Find
 * @docs docs/data-structure/rollback-union-find.md
 */