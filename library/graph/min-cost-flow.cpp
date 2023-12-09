#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define ll long long
constexpr ll mod = 1000000007;
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;

#define MAX_V 5005

struct edge {
	ll to, cap, cost, rev;
	edge(ll to, ll cap, ll cost, ll rev) : to(to), cap(cap), cost(cost), rev(rev) {}
};

ll n;
vector<edge> g[MAX_V];
ll dist[MAX_V];
ll prevv[MAX_V], preve[MAX_V];

void add_edge(ll from, ll to, ll cap, ll cost) {
	g[from].emplace_back(to, cap, cost, g[to].size());
	g[to].emplace_back(from, 0, -cost, g[from].size() - 1);
}

ll min_cost_flow(ll s, ll t, ll f) {
	ll res = 0;
	while(f > 0) {
		fill(dist, dist + n, INF);
		dist[s] = 0;
		bool update = true;
		while(update) {
			update = false;
			rep(v, 0, n) {
				if(dist[v] == INF) continue;
				rep(i, 0, g[v].size()) {
					edge &e = g[v][i];
					if(e.cap > 0 && dist[e.to] > dist[v] + e.cost) {
						dist[e.to] = dist[v] + e.cost;
						prevv[e.to] = v;
						preve[e.to] = i;
						update = true;
					}
				}
			}
		}
		if(dist[t] == INF) {
			return -1;
		}
		ll d = f;
		for(ll v = t; v != s; v = prevv[v]) {
			d = min(d, g[prevv[v]][preve[v]].cap);
		}
		f -= d;
		res += d * dist[t];
		for(ll v = t; v != s; v = prevv[v]) {
			edge &e = g[prevv[v]][preve[v]];
			e.cap -= d;
			g[v][e.rev].cap += d;
		}
	}
	return res;
}