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

vector<ll> EulerianTrail(vector<vector<ll>>& g, ll s, ll directed) {
    ll n = g.size();
    struct Edge { ll to, id; };
    vector<vector<Edge>> adj(n);
    ll eid = 0;
    rep(u,0,n) {
        for(auto v : g[u]) {
            adj[u].push_back({v, eid});
            if (!directed) {
                adj[v].push_back({u, eid});
            }
            ++eid;
        }
    }
    ll m = eid;
    vector<bool> used(m, false);
    vector<ll> ptr(n, 0);
    vector<ll> trail, stk;
    stk.reserve(m + 1);

    stk.push_back(s);
    while (!stk.empty()) {
        ll u = stk.back();
        while (ptr[u] < adj[u].size() && used[adj[u][ptr[u]].id]) {
            ++ptr[u];
        }
        if (ptr[u] == adj[u].size()) {
            trail.push_back(u);
            stk.pop_back();
        } else {
            auto e = adj[u][ptr[u]++];
            used[e.id] = true;
            stk.push_back(e.to);
        }
    }
    for (bool u : used) {
        if (!u) return {}; 
    }
    reverse(trail.begin(), trail.end());
    return trail;
}