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
    ll h, w; cin >> h >> w;
    vector<vector<ll>> a(h,vector<ll>(w));
    rep(i,0,h)rep(j,0,w) cin >> a[i][j];
    rep(i,0,h){
        bool flg = true;
        rep(j,0,w) if(a[i][j] != 0) flg = false;
        if(flg) rep(j,0,w) a[i][j] = 1;
    }
    {
        vector<tuple<ll,ll,ll>> vec;
        rep(i,0,h){
            ll l = INF, r = -INF;
            rep(j,0,w) if(a[i][j] != 0){
                chmin(l,a[i][j]);
                chmax(r,a[i][j]);
            }
            vec.push_back({l,r,i});
        }
        sort(vec.begin(), vec.end());
        rep(i,0,vec.size()-1){
            if(get<1>(vec[i]) > get<0>(vec[i+1])){
                cout << "No" << endl;
                return 0;
            }
        }
    }
    tsort ts(h*w*2);
    rep(i,0,h){
        vector<pll> vec;
        rep(j,0,w) if(a[i][j] != 0) vec.push_back({a[i][j],j});
        sort(vec.begin(), vec.end());
        ll idx = 0, pre = -1;
        while(idx < vec.size()){
            ll x = idx;
            while(idx < vec.size() && vec[idx].first == vec[x].first){
                ts.add_edge(vec[idx].second,i*w+vec[x].second+h*w);
                if(pre != -1)ts.add_edge(pre, vec[idx].second);
                idx++;
            }
            pre = i*w+vec[x].second+h*w;
        }

    }
    if(ts.solve()) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}