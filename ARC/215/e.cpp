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
        rep(i,0,mp.size()) res.push_back(mp[i]);
        return res;
    }
};
void solve(){
    ll n; cin >> n;
    vector<ll> a(n), b(n);
    {
        string a_, b_; cin >> a_ >> b_;
        rep(i,0,n) a[i] = a_[i]-'0';
        rep(i,0,n) b[i] = b_[i]-'0';
    }
    ll m; cin >> m;
    vector<vector<ll>> g(n), revg(n);
    vector<vector<pll>> g2(n);
    rep(i,0,m){
        ll x, y; cin >> x >> y;
        x--;y--;
        g[x].push_back(y);
        revg[y].push_back(x);
        g2[x].push_back({y,i+1});
    }
    // cout << "a" << endl;
    StronglyConnectedComponents scc(g);
    vector<ll> com = scc.component;
    vector<vector<ll>> gg = scc.rebuild();
    vector<vector<ll>> revgg(gg.size());
    vector<vector<ll>> mp = scc.scc();
    vector<ll> is_root(n,1), a1(n), b1(n), loop(n), l2(n), revc(gg.size());
    vector<ll> start(n,-1);
    // for(auto x: com) cout << x << " ";
    // cout << endl;
    rep(i,0,n){
        a1[com[i]] += a[i];
        b1[com[i]] += b[i];
        for(auto x: g[i]){
            if(x == i){
                loop[com[i]] = 1;
                l2[x] = 1;
            }
        }
        if(i >= (ll) gg.size()) continue;
        for(auto x: gg[i]){
            // cout << x << " " << i << " " << gg.size() << endl;
            revgg[x].push_back(i);
            revc[x]++;
        }
    }
    vector<ll> ord;
    vector<ll> ans;
    // cout << "b" << endl;
    {
        queue<ll> q;
        rep(x,0,(ll)mp.size()){
            if(revc[x] == 0){
                q.push(x);
            }
        }
        while(!q.empty()){
            auto x = q.front();q.pop();
            ord.push_back(x);
            if(is_root[x]){
                if((!a1[x] && b1[x]) || (a1[x] && !b1[x] && !loop[x])){
                    cout << -1 << endl;
                    return;
                }
            }
            for(auto nx: gg[x]){
                if(!is_root[x] || a1[x]) is_root[nx] = 0; 
                revc[nx]--;
                if(revc[nx] == 0) q.push(nx);
            }
            if(is_root[x] && !a1[x]) continue;
            for(auto v: mp[x]){
                for(auto vv: g[v]){
                    if(!is_root[com[vv]] && com[vv] != x) start[com[vv]] = vv;
                }
            }
        }
    }
    // cout << "c" << endl;
    ll osz = ord.size();
    vector<ll> root_w(osz,-1);
    auto black = [&](ll gr) -> void {
        // cout << gr << endl;
        if(!a1[gr]) return;
        // cout << gr << endl;
        queue<ll> q;
        for(auto v: mp[gr]){
            // cout << gr << " " << v << endl;
            if(a[v]) q.push(v);
        }
        while(!q.empty()){
            auto v = q.front(); q.pop();
            // cout << v << endl;
            for(auto [nv, id]: g2[v]){
                if(!a[nv]){
                    // cout << nv << " " << id << endl;
                    ans.push_back(id);
                    a[nv] = 1;
                    a1[com[nv]]++;
                    if(com[nv] == gr) q.push(nv);
                }
            }
        }
    };
    vector<ll> check(n);
    auto white = [&](ll gr) -> void {
        if(!a1[gr]) return;
        ll s = start[gr];
        for(auto v: mp[gr]){
            if(b[v] || l2[v]) s = v;
        }
        auto dfs = [&](auto dfs, ll v) -> void {
            check[v] = 1;
            for(auto [nv,id]: g2[v]){
                if(!check[nv] && com[nv] == gr){
                    dfs(dfs,nv);
                    if(a[v] && a[nv] && !b[nv]){
                        ans.push_back(id);
                        a[nv] = 0;
                        a1[com[nv]]--;
                    }
                } 
            }
            for(auto [nv,id] : g2[v]){
                if(com[v] != com[nv] && !b[nv] && a[nv]){
                    ans.push_back(id);
                    a[nv] = 0;
                    a1[com[nv]]--;
                }
            }
            for(auto [nv,id] : g2[v]){
                if(v == nv && !b[v] && a[nv]){
                    ans.push_back(id);
                    a[v] = 0;
                    a1[com[v]]--;
                }
            }
        };
        dfs(dfs,s);
    };
    rep(i,0,osz) black(ord[i]); 
    // cout << "d" << endl;
    rrep(i,osz-1,0) white(ord[i]);
    cout << ans.size() << endl;
    for(auto x: ans) cout << x << " ";
    cout << endl;
    // cout << "e" << endl;
}

int main() {
    ll t; cin >> t;
    while(t--) solve();
    return 0;
}