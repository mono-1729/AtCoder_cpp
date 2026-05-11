#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <stdlib.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define inr(l, x, r) (l <= x && x < r)
#define ll long long
#define ld long double
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

ll gcd(ll a, ll b){
    if(b == 0) return a;
    if(a%b == 0){
      return b;
    }else{
      return gcd(b, a%b);
    }
}

ll lcm(ll a, ll b){
    return a*b / gcd(a, b);
}

ll powMod(ll x, ll n, ll mod) {
    if (n == 0) return 1 % mod;
    ll val = powMod(x, n / 2, mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}

class tsort {
public:
	int V;
	vector<vector<int> > G;
	vector<int> deg,res;
	tsort(int node_size) : V(node_size), G(V), deg(V, 0){}
	void add_edge(int from,int to){
		G[from].push_back(to);
		deg[to]++;
	}
	bool solve() {
		queue<int> que;
		for(int i = 0; i < V; i++){
			if(deg[i] == 0){
				que.push(i);
			}
		}
		while(!que.empty()){
			int p = que.front();
			que.pop();
			res.push_back(p);
			for(int v : G[p]){
				if(--deg[v] == 0){
					que.push(v);
				}
			}
		}
		return (*max_element(deg.begin(),deg.end()) == 0);
	}
};

int main() {
    ll t; cin >> t;
    while(t--){
        ll n, m; cin >> n >> m;
        vector<vector<ll>> g(n);
        tsort ts(n);
        rep(i,0,m){
            ll u, v; cin >> u >> v;
            u--;v--;
            g[u].push_back(v);
            ts.add_edge(u,v);
        }
        vector<mint> num(n);
        ts.solve();
        vector<int> res = ts.res;
        num[0] = 1;
        rrep(i,n-2,0) if(res[i+1] == 0) swap(res[i],res[i+1]);
        for(auto x: res){
            for(auto y: g[x]) num[y] += num[x];
        }
        cout << num[n-1].val() << endl;
    }
    return 0;
}
