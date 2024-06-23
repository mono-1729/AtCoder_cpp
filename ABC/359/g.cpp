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

template< typename T >
struct SparseTable {
  vector< vector< T > > st;
  vector< int > lookup;

  SparseTable() {};

  SparseTable(const vector< T > &v) {
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
        g=G;
        n=g.size();
        in.assign(n,-1);out.assign(n,-1);
        cnt = 0;
        dfs(0,-1,0);
        depth_.push_back({0,0});
        depth=SparseTable<pll>(depth_);
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
        ll ret = depth.rmq(l,r).first;
        return abs(depth_[in[u]].first - ret) + abs(depth_[in[v]].first - ret);
    }
};

ll border = 400;

int main() {
    ll n; cin >> n;
    vector<vector<ll>> g(n);
    rep(i, 0, n-1){
        ll a, b; cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    EulerTour et(g);
    vector<ll> a(n),acnt(n+1);
    vector<vector<ll>> apos(n+1);
    rep(i, 0, n){
        cin >> a[i];
        acnt[a[i]]++;
        apos[a[i]].push_back(i);
    }
    unordered_map<ll, ll> mp;
    vector<ll> inv;
    ll cnt = 0;
    rep(i,0,n){
        if(acnt[i] >= border){
            mp[i] = cnt;
            inv.push_back(i);
            cnt++;
        }
    }
    vector<vector<ll>> dp(n, vector<ll>(cnt, 0));
    ll ans = 0;
    auto dfs([&](auto self, ll v, ll p) -> void {
        if(acnt[a[v]] >= border){
            dp[v][mp[a[v]]]++;
        }
        for(auto nv : g[v]){
            if(nv == p) continue;
            self(self, nv, v);
            rep(i, 0, cnt){
                dp[v][i] += dp[nv][i];
                ans += dp[nv][i] * (acnt[inv[i]] - dp[nv][i]);
            }
        }
    });
    dfs(dfs, 0, -1);
    rep(i, 0, n+1){
        if(acnt[i] < border){
            rep(j, 0, acnt[i]){
                rep(k, j+1, acnt[i]){
                    ans += et.lca(apos[i][j], apos[i][k]);
                    // cout << et.lca(apos[i][j], apos[i][k]) << " " << apos[i][j] << " " << apos[i][k] << endl;
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}