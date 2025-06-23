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

#define MAX_V 2002

struct edge {
	ll to, cap, cost, rev;
	edge(ll to, ll cap, ll cost, ll rev) : to(to), cap(cap), cost(cost), rev(rev) {}
};

ll Vx=MAX_V;
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
		fill(dist, dist + Vx, INF);
		dist[s] = 0;
		bool update = true;
		while(update) {
			update = false;
			rep(v, 0, Vx) {
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

int main() {
    ll h, w; cin >> h >> w;
    vector<vector<ll>> a(h,vector<ll>(w));
    ll ans = 0;
    rep(i,0,h)rep(j,0,w) cin >> a[i][j], ans += a[i][j];
    ll cnt = ans;
    ll c = 1LL << 41;
    ll s = h*w, t = h*w+1;
    rep(i,0,h)rep(j,0,w){
        ll v = i*w+j;
        if((i+j)%2 == 0){
            add_edge(s,v,1,0);
            if(i < h-1) add_edge(v,v+w,1,c+a[i][j]+a[i+1][j]);
            if(j < w-1) add_edge(v,v+1,1,c+a[i][j]+a[i][j+1]);
            if(i > 0) add_edge(v,v-w,1,c+a[i][j]+a[i-1][j]);
            if(j > 0) add_edge(v,v-1,1,c+a[i][j]+a[i][j-1]);
        }else add_edge(v,t,1,0);
    }
    while(true){
        ll x = min_cost_flow(s,t,1);
        if(x == -1) break;
        cnt += c-x;
        chmax(ans,cnt);
    }
    cout << ans << endl;
    return 0;
}