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

#define MAX_V 5000

struct edge {
	ll to, cap, rev;
	edge(ll to, ll cap, ll rev) : to(to), cap(cap), rev(rev) {}
};

vector<edge> g[MAX_V];
ll level[MAX_V];
ll iter[MAX_V];

void add_edge(ll from, ll to, ll cap) {
	g[from].emplace_back(to, cap, g[to].size());
	g[to].emplace_back(from, 0, g[from].size() - 1);
}

void bfs(ll s) {
	memset(level, -1, sizeof(level));
	queue<ll> que;
	level[s] = 0;
	que.push(s);
	while(!que.empty()) {
		ll v = que.front(); que.pop();
		for(auto &e : g[v]) {
			if(e.cap > 0 && level[e.to] < 0) {
				level[e.to] = level[v] + 1;
				que.push(e.to);
			}
		}
	}
}

ll dfs(ll v, ll t, ll f) {
	if(v == t) return f;
	for(ll &i = iter[v]; i < g[v].size(); i++) {
		edge &e = g[v][i];
		if(e.cap > 0 && level[v] < level[e.to]) {
			ll d = dfs(e.to, t, min(f, e.cap));
			if(d > 0) {
				e.cap -= d;
				g[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}

ll max_flow(ll s, ll t) {
	ll flow = 0;
	while(true) {
		bfs(s);
		if(level[t] < 0) return flow;
		memset(iter, 0, sizeof(iter));
		ll f;
		while((f = dfs(s, t, 1e18)) > 0) {
			flow += f;
		}
	}
}

vector<ll> mincut(ll s) {
    vector<ll> ret(MAX_V);
    queue<ll> que;
    que.push(s);
    ret.push_back(s);
    while(!que.empty()) {
        ll v = que.front(); que.pop();
        for(auto &e : g[v]) {
            if(e.cap > 0 && ret[e.to] == 0) {
                que.push(e.to);
                ret[e.to] = 1;
            }
        }
    }
    return ret;
}

int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> wl(n,vector<int>(n,-1));
    rep(i,0,n) wl[i][i] = 0;
    rep(i,0,m){
        ll w, l; cin >> w >> l;
        w--;l--;
        wl[w][l] = 1;
        wl[l][w] = 0;
    }
    rep(i,0,n){
        int rest_cnt = 0;
        vector<vector<int>> tmp = wl;
        rep(j,0,n) if(tmp[i][j] == -1){
            tmp[i][j] = 1;
            tmp[j][i] = 0;
        }
        vector<int> wincnt(n,0);
        rep(j,0,n)rep(k,0,n) if(tmp[j][k] == 1) wincnt[j]++;
        rep(j,0,n)rep(k,j,n){
            if(tmp[j][k] == -1){
                rest_cnt++;
                add_edge(3000,j*n+k,1);
                add_edge(j*n+k,j+2000,1);
                add_edge(j*n+k,k+2000,1);
            }
        }
        bool flg = true;
        rep(j,0,n){
            if(i == j) continue;
            if(wincnt[i] <= wincnt[j]){
                flg = false;
                break;
            }
            add_edge(j+2000,4000,wincnt[i]-wincnt[j]-1);
        }
        // cout << max_flow(3000,4000) << " " << rest_cnt << " " << i+1 << endl;
        if(flg && max_flow(3000,4000) == rest_cnt) cout << i+1 << " ";
        rep(i,0,MAX_V) g[i].clear();
        rep(i,0,MAX_V) level[i] = 0;
        rep(i,0,MAX_V) iter[i] = 0;
    }
    cout << endl;
    return 0;
}