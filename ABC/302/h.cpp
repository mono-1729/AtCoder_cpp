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
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint998244353;

ll gcd(ll a, ll b){
    if(a%b == 0){
      return b;
    }else{
      return gcd(b, a%b);
    }
}

ll lcm(ll a, ll b){
    return a*b / gcd(a, b);
}

ll powMod(ll x, ll n) {
    if (n == 0) return 1 % MOD;
    ll val = powMod(x, n / 2);
    val *= val;
    val %= MOD;
    if (n % 2 == 1) val *= x;
    return val % MOD;
}

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

int main() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    rep(i,0,n) cin >> a[i] >> b[i], a[i]--, b[i]--;
    vector<vector<int>> g(n);
    rep(i,0,n-1){
        int u, v; cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    RollbackUnionFind uf(n);
    vector<int> edgecnt(n,0);
    int ans = 0;
    vector<int> cnt(n);
    auto dfs = [&](auto dfs, int v, int par) -> void {
        int ap = uf.find(a[v]);
        int bp = uf.find(b[v]);
        int ea = edgecnt[ap];
        int eb = edgecnt[bp];
        bool f = false;
        int preans = ans;
        if(uf.same(a[v], b[v])){
            ans -= min((int)edgecnt[ap], uf.size(ap));
            edgecnt[ap]++;
            ans += min((int)edgecnt[ap], uf.size(ap));
        }
        else{
            f = true;
            ans -= min((int)edgecnt[ap], uf.size(ap));
            ans -= min((int)edgecnt[bp], uf.size(bp));
            edgecnt[ap] = edgecnt[bp] = 0;
            uf.unite(a[v], b[v]);
            edgecnt[uf.find(a[v])] = ea + eb + 1;
            ans += min((int) ea + (int) eb + 1, uf.size(ap));
        }
        cnt[v] = ans;
        for(auto nv : g[v]){
            if(nv == par) continue;
            dfs(dfs, nv, v);
        }
        if(f) uf.undo();
        edgecnt[ap] = ea;
        edgecnt[bp] = eb;
        ans = preans;
    };
    
    dfs(dfs, 0, -1);
    rep(i,1,n) cout << cnt[i] << " ";
    cout << endl;
    return 0;
}