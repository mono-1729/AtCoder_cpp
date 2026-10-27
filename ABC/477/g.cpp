#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <stdlib.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define inr(l, x, r) (l <= x && x < r)
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define all(x) (x).begin(), (x).end()
//constexpr ll MOD = 1000000007;
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint998244353;

ll gcd(ll a, ll b){
    if(b == 0) return a;
    if(a%b == 0){
      return b;
    }else{
      return gcd(b, a%b);
    }
}

ll lcm(ll a, ll b){
    return a*b / gcd(a, b);
}

ll powMod(ll x, ll n, ll mod) {
    if (n == 0) return 1 % mod;
    ll val = powMod(x, n / 2, mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}

struct Mo {
  int n;
  vector< pair< int, int > > lr;

  explicit Mo(int n) : n(n) {}

  void add(int l, int r) { /* [l, r) */
    lr.emplace_back(l, r);
  }

  template< typename AL, typename AR, typename EL, typename ER, typename O >
  void build(const AL &add_left, const AR &add_right, const EL &erase_left, const ER &erase_right, const O &out) {
    int q = (int) lr.size();
    int bs = n / min< int >(n, sqrt((double)q));
    vector< int > ord(q);
    iota(begin(ord), end(ord), 0);
    sort(begin(ord), end(ord), [&](int a, int b) {
      int ablock = lr[a].first / bs, bblock = lr[b].first / bs;
      if(ablock != bblock) return ablock < bblock;
      return (ablock & 1) ? lr[a].second > lr[b].second : lr[a].second < lr[b].second;
    });
    int l = 0, r = 0;
    for(auto idx : ord) {
      while(l > lr[idx].first) add_left(--l);
      while(r < lr[idx].second) add_right(r++);
      while(l < lr[idx].first) erase_left(l++);
      while(r > lr[idx].second) erase_right(--r);
      out(idx);
    }
  }

  template< typename A, typename E, typename O >
  void build(const A &add, const E &erase, const O &out) {
    build(add, add, erase, erase, out);
  }
};

template< typename T >
struct SparseTable {
  vector< vector< T > > st;
  vector< int > lookup;

  SparseTable() {};

  SparseTable(const vector< T > &v) {
    int b = 0;
    while((1 << b) <= (int)v.size()) ++b;
    st.assign(b, vector< T >(1 << b));
    for(int i = 0; i < (int)v.size(); i++) {
      st[0][i] = v[i];
    }
    for(int i = 1; i < b; i++) {
      for(int j = 0; j + (1 << i) <= (1 << b); j++) {
        st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
      }
    }
    lookup.resize(v.size() + 1);
    for(int i = 2; i < (int)lookup.size(); i++) {
      lookup[i] = lookup[i >> 1] + 1;
    }
  }

  void init(const vector< T > &v) {
    int b = 0;
    while((1 << b) <= v.size()) ++b;
    st.assign(b, vector< T >(1 << b));
    for(int i = 0; i < v.size(); i++) {
      st[0][i] = v[i];
    }
    for(int i = 1; i < b; i++) {
      for(int j = 0; j + (1 << i) <= (1 << b); j++) {
        st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
      }
    }
    lookup.resize(v.size() + 1);
    for(int i = 2; i < lookup.size(); i++) {
      lookup[i] = lookup[i >> 1] + 1;
    }
  }

  inline T rmq(int l, int r) {
    int b = lookup[r - l];
    return min(st[b][l], st[b][r - (1 << b)]);
  }
};


struct EulerTour {
    int n;
    int cnt;
    vector<vector<ll>> g;
    vector<ll> in,out;
    vector<pll> depth_; 
    SparseTable<pll> depth;

    EulerTour(vector<vector<ll>> &G){
        g = G;
        n = (int)g.size();
        in.assign(n,-1); out.assign(n,-1);
        cnt = 0;
        dfs(0, -1, 0);
        depth_.push_back({0, 0});
        depth = SparseTable<pll>(depth_);
    }

    void dfs(ll v, ll p,ll d){
        in[v]=depth_.size();
        depth_.push_back({d,v});
        for(auto to:g[v]){
            if(to==p)continue;
            dfs(to,v,d+1);
            depth_.push_back({d,v});
        }
        out[v]=depth_.size();
    }

    ll lca(ll u,ll v){
        ll l = min(in[u],in[v]), r = max(out[u],out[v]);
        return depth.rmq(l,r).second;
    }

    ll dep(ll u){
        return depth.rmq(in[u], in[u]+1).first;
    }
};

int main() {
    ll n, q; cin >> n >> q;
    vector<ll> x(n);
    rep(i,0,n) cin >> x[i], x[i]--;
    vector<vector<ll>> g(n);
    rep(i,0,n-1){
        ll u, v; cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    EulerTour et(g);
    vector<ll> in(n), vec;
    auto dfs = [&](auto dfs, ll v, ll p) -> void {
        in[v] = vec.size();
        vec.push_back(v);
        for(auto nv: g[v]){
            if(nv == p) continue;
            dfs(dfs,nv,v);
        }
        vec.push_back(v);
    };
    dfs(dfs,0,-1);
    Mo mo(2*n);
    vector<tuple<ll,ll,ll,ll>> query(q);
    rep(i,0,q){
        ll s, t, a, b; cin >> s >> t >> a >> b;
        s--;t--;
        query[i] = {s,t,a,b+1};
        mo.add(min(in[s],in[t])+1, max(in[s],in[t])+1);
    }
    vector<ll> ans(q), cnt(n), sum(n+2), on(n);
    sum[0] = n;
    auto add = [&](int i) {
        // cout << "add " << i << endl;
        ll c = x[vec[i]];
        if(on[vec[i]]){
            sum[cnt[c]]--;
            cnt[c]--;
            on[vec[i]] = 0;
        }else{
            cnt[c]++;
            on[vec[i]] = 1;
            sum[cnt[c]]++;
        }
    };
    auto addi = [&](int vi) {
        ll c = x[vi];
        if(on[vi]){
            sum[cnt[c]]--;
            cnt[c]--;
            on[vi] = 0;
        }else{
            cnt[c]++;
            on[vi] = 1;
            sum[cnt[c]]++;
        }
    };
    auto out = [&](int id) {
        auto [s,t,l,r] = query[id];
        // cout << "out! " << id << endl;
        // cout << l << " " << r << endl;
        addi(et.lca(s,t));
        ans[id] = sum[l]-sum[r];
        addi(et.lca(s,t));
    };
    mo.build(add, add, out);
    for(auto c: ans) cout << c << endl;
    return 0;
}