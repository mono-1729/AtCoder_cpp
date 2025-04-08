#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define ll long long


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