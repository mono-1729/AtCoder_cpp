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
#define all(x) (x).begin(), (x).end()
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

class UnionFind {
    vector<ll> parent, maxi, mini;
    inline ll root(ll n){
        return (parent[n] < 0? n:parent[n] = root(parent[n]));
    }
public:
    UnionFind(ll n_ = 1): parent(n_, -1), maxi(n_), mini(n_){
        iota(maxi.begin(), maxi.end(), 0);
        iota(mini.begin(), mini.end(), 0);
    }

    inline bool same(ll x, ll y){
        return root(x) == root(y);
    }

    inline void unite(ll x, ll y){
        ll rx = root(x);
        ll ry = root(y);
        if(rx == ry) return;
        if(parent[rx] > parent[ry]) swap(rx, ry);
        parent[rx] += parent[ry];
        parent[ry] = rx;
        maxi[rx] = std::max(maxi[rx],maxi[ry]);
        mini[rx] = std::min(mini[rx],mini[ry]);
    }

    inline ll min(ll x){
        return mini[root(x)];
    }

    inline ll max(ll x){
        return maxi[root(x)];
    }

    inline ll size(ll x){
        return (-parent[root(x)]);
    }

    inline ll operator[](ll x){
        return root(x);
    }

    inline void print(){
        rep(i, 0, (ll)parent.size()) cout << root(i) << " ";
        cout << endl;
    }

    void clear(){
        rep(i, 0, (ll)parent.size()){
            parent[i] = -1;
        }
        iota(maxi.begin(), maxi.end(), 0);
        iota(mini.begin(), mini.end(), 0);
    }
};

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
    vector<ll> a(m), b(m), c(m), d(m);
    auto no = [&](){
        cout << "No" << endl;
        exit(0);
    };
    UnionFind uf(n);
    rep(i,0,m){
        cin >> a[i] >> b[i] >> c[i] >> d[i];
        a[i]--;b[i]--;c[i]--;d[i]--;
    }
    ll cnt = 0;
    vector<ll> ok(m,0);
    while(cnt < m){
        vector<vector<ll>> g(n);
        rep(i,0,m){
            if(ok[i]) continue;
            while(true){
                if(uf[a[i]] == uf[c[i]]){
                    a[i]++, c[i]++;
                    if(c[i] > d[i]) no();
                    else if(a[i] > b[i]){
                        ok[i] = 1;
                        cnt++;
                        break;
                    }
                }else{
                    g[uf[a[i]]].push_back(uf[c[i]]);
                    break;
                }
            }
        }
        StronglyConnectedComponents scc(g);
        vector<vector<ll>> h = scc.scc();
        if(h.size() == n) break;
        else{
            for(auto vec: h){
                ll x = vec[0];
                rep(j,1,vec.size()){
                    uf.unite(x,vec[j]);
                }
            }
        }
    }
    cout << "Yes" << endl;
    return 0;
}