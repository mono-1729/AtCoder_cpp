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

template <class Cap> 
class Dinic {
    int _n;
    struct _edge {
        int to, rev;
        Cap cap;
    };
    vector<pair<int, int>> pos;
    vector<vector<_edge>> g;

public:
    Dinic(): _n(0) {}
    explicit Dinic(int n): _n(n), g(n) {}

    int add_edge(int from, int to, Cap cap){
        assert(0 <= from && from < _n);
        assert(0 <= to && to < _n);
        assert(0 <= cap);
        int m = (int)pos.size();
        pos.push_back({from, (int)g[from].size()});
        int from_id = (int)g[from].size();
        int to_id = (int)g[to].size();
        if(from == to) to_id++;
        g[from].push_back(_edge{to, to_id, cap});
        g[to].push_back(_edge{from, from_id, 0});
        return m;
    }

    struct edge{
        int from, to;
        Cap cap, flow;
    };

    edge get_edge(int i){
        int m = (int)pos.size();
        assert(0 <= i && i < m);
        auto _e = g[pos[i].first][pos[i].second];
        auto _re = g[_e.to][_e.rev];
        return edge{pos[i].first, _e.to, _e.cap+_re.cap, _re.cap};
    }

    vector<edge> edges(){
        int m = (int)pos.size();
        vector<edge> result;
        for(int i = 0; i < m; i++){
            result.push_back(get_edge(i));
        }
        return result;
    }

    void change_edge(int i, Cap new_cap, Cap new_flow){
        int m = (int)pos.size();
        assert(0 <= i && i < m);
        assert(0 <= new_flow && new_flow <= new_cap);
        auto& _e = g[pos[i].first][pos[i].second];
        auto& _re = g[_e.to][_e.rev];
        _e.cap = new_cap-new_flow;
        _re.cap = new_flow;
    }

    Cap flow(int s, int t){
        return flow(s, t, numeric_limits<Cap>::max());
    }
    // s!=t である必要あり
    Cap flow(int s, int t, Cap flow_limit){
        assert(0 <= s && s < _n);
        assert(0 <= t && t < _n);
        assert(s != t);

        vector<int> level(_n), iter(_n);
        queue<int> que;

        auto bfs = [&]()->void {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            queue<int>().swap(que);
            que.push(s);
            while(!que.empty()){
                int v = que.front(); que.pop();
                for(auto e: g[v]){
                    if(e.cap == 0 || level[e.to] >= 0) continue;
                    level[e.to] = level[v]+1;
                    if(e.to == t) return;
                    que.push(e.to);
                }
            }
        };

        auto dfs = [&](auto self, int v, Cap up)->Cap {
            if(v == s) return up;
            Cap res = 0;
            int level_v = level[v];
            for(int& i = iter[v]; i < (int)g[v].size(); i++){
                _edge& e = g[v][i];
                if(level_v <= level[e.to] || g[e.to][e.rev].cap == 0) continue;
                Cap d = self(self, e.to, min(up-res, g[e.to][e.rev].cap));
                if(d <= 0) continue;
                g[v][i].cap += d;
                g[e.to][e.rev].cap -= d;
                res += d;
                if(res == up) return res;
            }
            level[v] = _n;
            return res;
        };
        
        Cap flow = 0;
        while(flow < flow_limit){
            bfs();
            if(level[t] == -1) break;
            fill(iter.begin(), iter.end(), 0);
            Cap f = dfs(dfs, t, flow_limit-flow);
            if(!f) break;
            flow += f;
        }
        return flow;
    }

    // 最小カットをした上で、頂点 s 側に属する頂点集合を返す
    vector<bool> min_cut(int s){
        vector<bool> visited(_n);
        queue<int> que;
        while(!que.empty()){
            int p = que.front(); que.pop();
            visited[p] = true;
            for(auto e: g[p]){
                if(e.cap && !visited[e.to]){
                    visited[e.to] = true;
                    que.push(e.to);
                }
            }
        }
        return visited;
    }
};

vector<ll> Z_algorithm(string S) {
	ll c = 0, n = S.size();
	vector<ll> Z(n, 0);
	for (ll i = 1; i < n; i++) {
		ll l = i - c;
		if (i + Z[l] < c + Z[c]) {
			Z[i] = Z[l];
		}
		else {
			ll j = max(0LL, c + Z[c] - i);
			while (i + j < n && S[j] == S[i + j])j++;
			Z[i] = j;
			c = i;
		}
	}
	Z[0] = n;
	return Z;
}

int main() {
    ll n; cin >> n;
    vector<string> s(n);
    rep(i,0,n) cin >> s[i];
    vector<ll> a(n);
    ll sum = 0;
    rep(i,0,n) cin >> a[i], sum += a[i];
    Dinic<ll> g(n*2+2);
    ll start = n*2, end = n*2+1;
    rep(i,0,n){
        g.add_edge(start, i, a[i]);
        g.add_edge(i+n, end, a[i]);
    }
    rep(i,0,n)rep(j,0,n){
        if(i == j) continue;
        if(s[i].size() < s[j].size()) continue;
        if(s[i].size() == s[j].size()){
            if(s[i] == s[j] && i < j) g.add_edge(i,j+n,INF);  
            continue;
        }
        vector<ll> vec = Z_algorithm(s[j]+s[i]);
        rep(k,s[j].size(), s[i].size()+s[j].size()){
            if(vec[k] >= s[j].size()){
                g.add_edge(i,j+n,INF);
                break;
            }
        }
    }
    cout << sum-g.flow(start,end) << endl;

    return 0;
}