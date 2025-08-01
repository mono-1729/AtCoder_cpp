#include <bits/stdc++.h>
#include <stdlib.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define inr(l, x, r) (l <= x && x < r)
#define ll long long
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
    vector<vector<ll>> rebuild() {
      ll N = *max_element(component.begin(), component.end()) + 1;
      vector<vector<ll>> rebuildedG(N);
      set<pair<ll, ll>> connected;
      for (ll v = 0; v < n; v++) {
        for (auto nv : G[v]) {
          if (component[v] != component[nv] and !connected.count(pair(v, nv))) {
            connected.insert(pair(v, nv));
            rebuildedG[component[v]].push_back(component[nv]);
          }
        }
      }
      return rebuildedG;
    }

    vector<vector<ll>> scc(){
        unordered_map<ll,vector<ll>> mp;
        rep(i,0,n) mp[component[i]].push_back(i);
        vector<vector<ll>> res;
        for(auto [key,val] : mp) res.push_back(val);
        return res;
    }
};

int main() {
    ll n, m; cin >> n >> m;
    vector<vector<ll>> g(n), revg(n);
    rep(i,0,m){
        ll s, t; cin >> s >> t;
        s--;t--;
        g[s].push_back(t);
        revg[t].push_back(s);
    }
    StronglyConnectedComponents scc(g);
    vector<ll> l(n), r(n);
    rep(i,0,n) cin >> l[i] >> r[i];
    if(scc.rebuild().size() != n){
        cout << "No" << endl;
        return 0;
    }
    {
        vector<ll> out(n);
        rep(i,0,n) out[i] = g[i].size();
        queue<ll> q;
        rep(i,0,n) if(out[i] == 0) q.push(i);
        while(!q.empty()){
            ll v = q.front(); q.pop();
            for(auto nv: g[v]) chmin(r[v],r[nv]-1);
            for(auto nv: revg[v]){
                out[nv]--;
                if(out[nv] == 0) q.push(nv);
            }
        }
    }
    vector<ll> ans(n);
    ll f = 1;
    {
        vector<ll> in(n);
        rep(i,0,n) in[i] = revg[i].size();
        priority_queue<pll,vector<pll>,greater<pll>> q;
        vector<vector<pll>> vec(n+1);
        rep(i,0,n) if(in[i] == 0) vec[l[i]].push_back({r[i],i});
        rep(i,1,n+1){
            for(auto x: vec[i]) q.push(x);
            if(q.empty()){
                f = 0;
                break;
            }
            auto [rx, id] = q.top();q.pop();
            if(rx < i){
                f = 0;
                break;
            }
            ans[id] = i;
            for(auto nv: g[id]){
                in[nv]--;
                if(in[nv] == 0){
                    if(l[nv] <= i) q.push({r[nv],nv});
                    else vec[l[nv]].push_back({r[nv],nv});
                }
            }
        }
    }
    if(f){
        cout << "Yes" << endl;
        for(auto x: ans) cout << x << " ";
        cout << endl;
    }else cout << "No" << endl;
    return 0;
}