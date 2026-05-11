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

struct StronglyConnectedComponents {
    ll n;
    vector<vector<ll>> G, rG;
    vector<ll> order, component;
    vector<bool> used;
    void dfs(ll v) {
      used[v] = 1;
      for (auto nv : G[v]) {
        if (!used[nv]) dfs(nv);
      }
      order.push_back(v);
    }
    void rdfs(ll v, ll k) {
      component[v] = k;
      for (auto nv : rG[v]) {
        if (component[nv] < 0) rdfs(nv, k);
      }
    }
  
    StronglyConnectedComponents(vector<vector<ll>> &_G) {
      n = _G.size();
      G = _G;
      rG.resize(n);
      component.assign(n, -1);
      used.resize(n);
      for (ll v = 0; v < n; v++) {
        for (auto nv : G[v]) rG[nv].push_back(v);
      }
      for (ll v = 0; v < n; v++) if (!used[v]) dfs(v);
      ll k = 0;
      reverse(order.begin(), order.end());
      for (auto v : order) if (component[v] == -1) rdfs(v, k), k++;
    }
  
    /// 頂点(u, v)が同じ強連結成分に含まれるか
    bool is_same(ll u, ll v) { return component[u] == component[v]; }
  
    /// 強連結成分を1つのノードに潰したグラフを再構築する
    pair<vector<ll>,vector<vector<ll>>> rebuild() {
      ll N = *max_element(component.begin(), component.end()) + 1;
      vector<vector<ll>> rebuildedG(N);
      vector<ll> cnt(N,0);
      set<pair<ll, ll>> connected;
      for (ll v = 0; v < n; v++) {
        cnt[component[v]]++;
        for (auto nv : G[v]) {
          if (component[v] != component[nv] and !connected.count(pair(v, nv))) {
            connected.insert(pair(v, nv));
            rebuildedG[component[v]].push_back(component[nv]);
          }
        }
      }
      return {cnt,rebuildedG};
    }

    vector<vector<ll>> scc(){
        unordered_map<ll,vector<ll>> mp;
        rep(i,0,n) mp[component[i]].push_back(i);
        vector<vector<ll>> res;
        rep(i,0,mp.size()) res.push_back(mp[i]);
        return res;
    }
};

int main() {
    ll n; cin >> n;
    vector<vector<ll>> g(n);
    rep(i,0,n)rep(j,0,n){
        ll f; cin >> f;
        if(f) g[i].push_back(j);
    }
    StronglyConnectedComponents scc(g);
    auto [sz,gg] = scc.rebuild();
    ll m = gg.size();
    vector<vector<ll>> revgg(m);
    vector<ll> incnt(m);
    rep(i,0,m){
        for(auto j: gg[i]){
            incnt[j]++;
            revgg[j].push_back(i);   
        }
    }
    queue<ll> q;
    vector<vector<ll>> dp(m+1,vector<ll>(m+1,-INF));
    dp[m][m] = 0;
    rep(i,0,m) if(sz[i] && incnt[i] == 0) q.push(i);
    
    while(!q.empty()){
        ll v = q.front(); q.pop();
        dp[v][m] = sz[v];
        rep(i,0,m)if(i != v) chmax(dp[i][v],dp[i][m]+sz[v]);
        for(auto pv: revgg[v]){
            rep(i,0,m){
                if(i == v) continue;
                chmax(dp[i][v], dp[i][pv]+sz[v]);
                chmax(dp[v][i], dp[pv][i]+sz[v]);
            }
            for(auto pv2: revgg[v]) chmax(dp[v][v],dp[pv][pv2]+sz[v]);
        }
        for(auto nv: gg[v]){
            incnt[nv]--;
            if(incnt[nv] == 0) q.push(nv);
        }
    }

    ll ans = 0;
    rep(i,0,m+1)rep(j,0,m+1) chmax(ans,dp[i][j]);
    cout << ans << endl;
    return 0;
}