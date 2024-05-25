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

#define MAX_V 5005

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

// 0ならば素数, 0でないなら最⼩の素因数
// 素因数分解や素因数の数も求めることが可能
ll max_num=20000005;
vector<ll> erat(max_num);
void init_e(){
    rep(i, 2, sqrt((double)max_num+1)){
        if(erat[i] == 0){
            for(ll j = i*i; j <= max_num-1; j += i){
                if(erat[j] == 0) erat[j] = i;
            }
        }
    }
}

int main() {
    init_e();
    ll n;cin>>n;
    vector<ll>a(n),b(n);
    rep(i,0,n)cin>>a[i]>>b[i];
    ll l = 0, r = 0;
    ll num1=0;
    rep(i,0,n)if(a[i]==1){
        num1=b[i];
        r = b[i]/2;
    } 
    auto solve = [&](ll x)->ll{
        rep(i,0,MAX_V)g[i].clear();
        ll s = 0, t = 300;
        rep(i,0,n){
            if(a[i]==1) add_edge(s,100+i,num1-x*2);
            else if(a[i]%2==1) add_edge(s,100+i,b[i]);
            else add_edge(200+i,300,b[i]);
        }
        rep(i,0,n)rep(j,0,n){
            if(a[i]%2==1 && a[j]%2==0 && erat[a[i]+a[j]]==0)add_edge(100+i,200+j,INF);
        }
        return max_flow(s,t)+x;
    };
    while(l+2<r){
        ll m1 = (l*2+r)/3;
        ll m2 = (l+r*2)/3;
        if(solve(m1)>solve(m2))r=m2;
        else l=m1;
    }
    ll ans = 0;
    rep(i,l,r+1)chmax(ans,solve(i));
    cout<<ans<<endl;
    return 0;
}