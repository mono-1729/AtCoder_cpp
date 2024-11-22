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
};

int main() {
    ll n = 6;
    vector<vector<ll>> g(n);
    vector<pll> uv = {{0,1},{1,2},{2,3},{1,4},{0,5}};
    for(auto [u,v]:uv){
        g[u].push_back(v);
        g[v].push_back(u);
    }
    EulerTour et(g);
    cout<<et.lca(1,4)<<endl;
    return 0;
}