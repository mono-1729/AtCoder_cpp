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
constexpr ll INF = 1LL<<60;

using S = pll;
S op1(S x1, S x2){return min(x1,x2); }
S e1() {return {INF,INF};}
using T = ll;
T op2(T x1, T x2){return x1+x2;}
T e2() {return 0;}

struct EulerTour {
    int n;
    int cnt;
    vector<vector<pll>> g;
    vector<ll> vcost;
    vector<ll> in,out;
    vector<pll> depth_; 
    segtree<S,op1,e1> depth;
    vector<ll> vcost1_,vcost2_,ecost1_,ecost2_;
    segtree<T,op2,e2> vcost1,vcost2,ecost1,ecost2;

    EulerTour(vector<vector<pll>> &G, vector<ll> vcost_){
        g=G;
        n=g.size();
        vcost=vcost_;
        in.assign(n,-1);out.assign(n,-1);
        cnt = 0;
        dfs(0,-1,0,0);
        vcost1_.push_back(0);
        vcost2_.push_back(-vcost[0]);
        ecost1_.push_back(0);
        ecost2_.push_back(0);
        depth_.push_back({0,0});
        depth=segtree<S,op1,e1>(depth_);
        vcost1=segtree<T,op2,e2>(vcost1_);
        vcost2=segtree<T,op2,e2>(vcost2_);
        ecost1=segtree<T,op2,e2>(ecost1_);
        ecost2=segtree<T,op2,e2>(ecost2_);
    }

    void dfs(ll v, ll p,ll d, ll ecost){
        in[v]=vcost1_.size();
        vcost1_.push_back(vcost[v]);
        vcost2_.push_back(vcost[v]);
        ecost1_.push_back(ecost);
        ecost2_.push_back(ecost);
        depth_.push_back({d,v});
        for(auto [to,cost]:g[v]){
            if(to==p)continue;
            dfs(to,v,d+1,cost);
            vcost1_.push_back(0);
            vcost2_.push_back(-vcost[to]);
            ecost1_.push_back(0);
            ecost2_.push_back(-cost);
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

    ll subTreeECost(ll u){
        return ecost1.prod(in[u]+1,out[u]);
    }

    ll rootPassVCost(ll u){
        return vcost2.prod(0,in[u]+1);
    }

    ll rootPassECost(ll u){
        return ecost2.prod(1,in[u]+1);
    }

    ll pathVCost(ll u, ll v){
        ll a = lca(u,v);
        return rootPassVCost(u)+rootPassVCost(v)-rootPassVCost(a)*2;
    }

    ll pathECost(ll u, ll v){
        ll a = lca(u,v);
        return rootPassECost(u)+rootPassECost(v)-rootPassECost(a)*2;
    }
};

int main() {
    ll n = 6;
    vector<vector<pll>> g(n);
    vector<ll> vcost = {1,2,3,4,5,6};
    vector<pll> uv = {{0,1},{1,2},{2,3},{1,4},{0,5}};
    for(auto [u,v]:uv){
        g[u].push_back({v,1});
        g[v].push_back({u,1});
    }
    EulerTour et(g,vcost);
    cout<<et.lca(1,4)<<endl;
    return 0;
}