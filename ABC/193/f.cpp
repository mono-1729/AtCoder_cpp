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

#define MAX_V 20000

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
    ll n; cin >> n;
    vector<vector<ll>> c(n,vector<ll>(n));
    rep(i,0,n)rep(j,0,n){
        char x; cin >> x;
        if(x == 'B') c[i][j] = 1;
        if(x == 'W') c[i][j] = 2;
        if(x == '?') c[i][j] = 3;
    }
    rep(i,0,n)rep(j,0,n){
        if((i+j)%2 == 0){
            if((c[i][j] & 1) == 0) add_edge(10000,i*n+j,INF); 
            if((c[i][j] & 2) == 0) add_edge(i*n+j,10001,INF); 
        }else{
            if((c[i][j] & 2) == 0) add_edge(10000,i*n+j,INF); 
            if((c[i][j] & 1) == 0) add_edge(i*n+j,10001,INF); 
        }
        if(i < n-1){
            add_edge(i*n+j,(i+1)*n+j,1);
            add_edge((i+1)*n+j,i*n+j,1);
        }
        if(j < n-1){
            add_edge(i*n+j,i*n+j+1,1);
            add_edge(i*n+j+1,i*n+j,1);
        }
    }
    cout << n*(n-1)+n*(n-1) - max_flow(10000,10001) << endl;
    return 0;
}