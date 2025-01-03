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

using S = pll;
S op1(S x1, S x2){return min(x1,x2); }
S e1() {return {INF,INF};}
using T = ll;
T op2(T x1, T x2){return x1+x2;}
T e2() {return 0;}

struct EulerTour {
    int n;
    int cnt;
    vector<vector<ll>> dpos;
    vector<vector<pll>> g;
    vector<ll> vcost;
    vector<ll> in,out;
    vector<pll> depth_; 
    segtree<S,op1,e1> depth;
    vector<ll> vcost1_;
    segtree<T,op2,e2> vcost1;

    EulerTour(vector<vector<pll>> &G){
        g=G;
        n=g.size();
        dpos.assign(n,vector<ll>());
        vcost=vector<ll>(n,0);
        in.assign(n,-1);out.assign(n,-1);
        cnt = 0;
        dfs(0,-1,0,0);
        vcost1_.push_back(0);
        depth_.push_back({0,0});
        depth=segtree<S,op1,e1>(depth_);
        vcost1=segtree<T,op2,e2>(vcost1_);
    }

    void dfs(ll v, ll p,ll d, ll ecost){
        in[v]=vcost1_.size();
        vcost1_.push_back(vcost[v]);
        depth_.push_back({d,v});
        dpos[d].push_back(v);
        for(auto [to,cost]:g[v]){
            if(to==p)continue;
            dfs(to,v,d+1,cost);
            vcost1_.push_back(0);
            depth_.push_back({d,v});
        }
        out[v]=vcost1_.size();
    }

    ll lca(ll u,ll v){
        ll l = min(in[u],in[v]), r = max(out[u],out[v]);
        return depth.prod(l,r).second;
    }

    ll subTreeVCost(ll u){
        return vcost1.prod(in[u],out[u]);
    }

    void updateVCost(ll u, ll x){
        vcost1.set(in[u],x);
    }
};

int main() {
    ll n; cin >> n;
    vector<ll> p(n);
    rep(i,1,n) cin >> p[i], p[i]--;
    vector<vector<pll>> g(n);
    rep(i,1,n){
        g[p[i]].push_back({i,1});
    }
    ll q; cin >> q;
    vector<vector<pll>> query(n);
    rep(i,0,q){
        ll u,d; cin >> u >> d;
        u--;
        query[d].push_back({u,i});
    }

    EulerTour et(g);
    vector<ll> ans(q);
    rep(d,0,n){
        for(auto u:et.dpos[d]){
            et.updateVCost(u,1);
        }
        for(auto [u,i]:query[d]){
            ans[i] = et.subTreeVCost(u);
        }
        for(auto u:et.dpos[d]){
            et.updateVCost(u,0);
        }
    }

    for(auto x:ans) cout << x << endl;

    return 0;
}