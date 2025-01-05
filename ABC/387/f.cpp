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

struct StronglyConnectedComponents {
  int n;
  vector<vector<int>> G, rG;
  vector<int> order, component;
  vector<bool> used;
  void dfs(int v) {
    used[v] = 1;
    for (auto nv : G[v]) {
      if (!used[nv]) dfs(nv);
    }
    order.push_back(v);
  }
  void rdfs(int v, int k) {
    component[v] = k;
    for (auto nv : rG[v]) {
      if (component[nv] < 0) rdfs(nv, k);
    }
  }

  StronglyConnectedComponents(vector<vector<int>> &_G) {
    n = _G.size();
    G = _G;
    rG.resize(n);
    component.assign(n, -1);
    used.resize(n);
    for (int v = 0; v < n; v++) {
      for (auto nv : G[v]) rG[nv].push_back(v);
    }
    for (int v = 0; v < n; v++) if (!used[v]) dfs(v);
    int k = 0;
    reverse(order.begin(), order.end());
    for (auto v : order) if (component[v] == -1) rdfs(v, k), k++;
  }

  /// 頂点(u, v)が同じ強連結成分に含まれるか
  bool is_same(int u, int v) { return component[u] == component[v]; }

  /// 強連結成分を1つのノードに潰したグラフを再構築する
  vector<vector<int>> rebuild() {
    int N = *max_element(component.begin(), component.end()) + 1;
    vector<vector<int>> rebuildedG(N);
    set<pair<int, int>> connected;
    for (int v = 0; v < n; v++) {
      for (auto nv : G[v]) {
        if (component[v] != component[nv] and !connected.count(pair(v, nv))) {
          connected.insert(pair(v, nv));
          rebuildedG[component[v]].push_back(component[nv]);
        }
      }
    }
    return rebuildedG;
  }
};

int main() {
    ll n, m; cin >> n >> m;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i], a[i]--;
    vector<vector<int>> g(n);
    rep(i,0,n) g[a[i]].push_back(i);
    StronglyConnectedComponents scc(g);
    vector<vector<int>> rg = scc.rebuild();
    vector<int> in(n, 0);
    rep(i,0,rg.size()){
        for(auto u: rg[i]) in[u]++;
    }
    mint ans = 1;

    auto solve = [&](auto solve, ll v) -> vector<mint> {
        vector<mint> dp(m+1, 0);
        dp[1] = 1;
        for(auto u: rg[v]){
            vector<mint> ndp(m+1, 0);
            vector<mint> p = solve(solve,u);
            mint sum1 = 0, sum2 = 0, sum3 = 0;
            rep(i,1,m+1){
                sum1 += dp[i];
                sum2 += p[i];
                ndp[i] = sum1 * sum2 - sum3;
                sum3 += ndp[i];
            }
            dp = ndp;
        }
        vector<mint> res(m+1, 0);
        rep(i,1,m+1) res[i] = res[i-1] + dp[i];
        return res;
    };
    rep(i,0,rg.size()){
        if(in[i] != 0) continue;
        vector<mint> dp = solve(solve,i);
        mint sum = 0;
        for(auto x: dp) sum += x;
        ans *= sum;
    }


    cout << ans.val() << endl;
    return 0;
}