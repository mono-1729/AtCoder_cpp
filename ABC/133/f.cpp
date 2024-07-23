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

using S = pll;
S op1(S x1, S x2){return min(x1,x2); }
S e1() {return {INF,INF};}
using T = ll;
T op2(T x1, T x2){return x1+x2;}
T e2() {return 0;}

struct EulerTour {
    int n;
    int cnt;
    vector<vector<tuple<ll,ll,ll>>> g;
    vector<ll> in,out;
    vector<ll> ecost2_;
    segtree<T,op2,e2> ecost2;
    vector<pll> depth_; 
    segtree<S,op1,e1> depth;
    vector<vector<ll>> plus, minus;

    EulerTour(vector<vector<tuple<ll,ll,ll>>> &G){
        g=G;
        n=g.size();
        in.assign(n,-1);out.assign(n,-1);
        plus = vector<vector<ll>>(100000); minus = vector<vector<ll>>(100000);
        cnt = 0;
        dfs(0,-1,0,-1,0);
        depth_.push_back({0,0});
        depth=segtree<S,op1,e1>(depth_);
        ecost2_.push_back(0);
        ecost2=segtree<T,op2,e2>(ecost2_);
    }

    void dfs(ll v, ll p,ll d,ll color, ll ecost){
        in[v]=ecost2_.size();
        if(color != -1) plus[color].push_back(ecost2_.size());
        ecost2_.push_back(ecost);
        depth_.push_back({d,v});
        for(auto [to,c,cost]:g[v]){
            if(to==p)continue;
            dfs(to,v,d+1,c,cost);
            minus[c].push_back(ecost2_.size());
            ecost2_.push_back(-cost);
            depth_.push_back({d,v});
        }
        out[v]=ecost2_.size();
    }

    ll lca(ll u,ll v){
        ll l = min(in[u],in[v]), r = max(out[u],out[v]);
        return depth.prod(l,r).second;
    }

    ll rootPassECost(ll u){
        return ecost2.prod(1,in[u]+1);
    }

    ll pathECost(ll u, ll v){
        ll a = lca(u,v);
        return rootPassECost(u)+rootPassECost(v)-rootPassECost(a)*2;
    }

    void color0(ll col){
        for(auto x: plus[col]) ecost2.set(x,0);
        for(auto x: minus[col]) ecost2.set(x,0);
    }
    void colorRev(ll col){
        for(auto x: plus[col]) ecost2.set(x,ecost2_[x]);
        for(auto x: minus[col]) ecost2.set(x,ecost2_[x]);
    }
    
};

struct EulerTour2 {
    int n;
    int cnt;
    vector<vector<tuple<ll,ll,ll>>> g;
    vector<ll> in,out;
    vector<ll> ecost2_;
    segtree<T,op2,e2> ecost2;
    vector<pll> depth_; 
    segtree<S,op1,e1> depth;
    vector<vector<ll>> plus, minus;

    EulerTour2(vector<vector<tuple<ll,ll,ll>>> &G){
        g=G;
        n=g.size();
        in.assign(n,-1);out.assign(n,-1);
        plus = vector<vector<ll>>(100000); minus = vector<vector<ll>>(100000);
        cnt = 0;
        dfs(0,-1,0,-1,0);
        depth_.push_back({0,0});
        depth=segtree<S,op1,e1>(depth_);
        ecost2_.push_back(0);
        ecost2=segtree<T,op2,e2>(ecost2_);
    }

    void dfs(ll v, ll p,ll d,ll color, ll ecost){
        in[v]=ecost2_.size();
        if(color != -1) plus[color].push_back(ecost2_.size());
        ecost2_.push_back(0);
        depth_.push_back({d,v});
        for(auto [to,c,cost]:g[v]){
            if(to==p)continue;
            dfs(to,v,d+1,c,cost);
            minus[c].push_back(ecost2_.size());
            ecost2_.push_back(0);
            depth_.push_back({d,v});
        }
        out[v]=ecost2_.size();
    }

    ll lca(ll u,ll v){
        ll l = min(in[u],in[v]), r = max(out[u],out[v]);
        return depth.prod(l,r).second;
    }

    ll rootPassECost(ll u){
        return ecost2.prod(1,in[u]+1);
    }

    ll pathECost(ll u, ll v){
        ll a = lca(u,v);
        return rootPassECost(u)+rootPassECost(v)-rootPassECost(a)*2;
    }

    
    void changeColor(ll col, ll cost){
        for(auto x: plus[col]) ecost2.set(x,cost);
        for(auto x: minus[col]) ecost2.set(x,-cost);
    }
};

int main() {
    ll n, q; cin >> n >> q;
    vector<ll> ans(q);
    vector<vector<tuple<ll,ll,ll>>> g(n);
    rep(i,0,n-1){
        ll a, b, c, d; cin >> a >> b >> c >> d;
        a--;b--;c--;
        g[a].push_back({b,c,d});
        g[b].push_back({a,c,d});
    }
    vector<vector<tuple<ll,ll,ll,ll>>> query(100000);
    rep(i,0,q){
        ll x, y, u, v; cin >> x >> y >> u >> v;
        x--;u--;v--;
        query[x].push_back({i,u,v,y});
    }
    EulerTour tour(g);
    EulerTour2 tour2(g);
    rep(col,0,100000){
        tour.color0(col);
        tour2.changeColor(col,1);
        for(auto[idx, u, v, x] : query[col]){
            ll num = tour.pathECost(u,v);
            num += tour2.pathECost(u,v) * x;
            ans[idx] = num;
        }
        tour2.changeColor(col,0);
        tour.colorRev(col);
    }
    rep(i,0,q) cout << ans[i] << endl;
    return 0;
}