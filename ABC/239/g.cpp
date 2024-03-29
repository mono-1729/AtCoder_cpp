#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
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
template <ll MOD> class modint {
    ll val;
    static vector<modint<MOD>> factorial_vec;
public:
    ll get() const { return (ll)val; }
    // コンストラクタ
    modint(ll x = 0){
        val = x % MOD;
        if(val < 0) x += MOD;
    }

    // 入出力ストリーム
    friend constexpr istream &operator>>(istream &is, modint<MOD> &x){
        ll y; is >> y;
        x = y;
        return is;
    }
    friend constexpr ostream &operator<<(ostream &os, const modint<MOD> &x){
        return os << x.val;
    }

    // 算術演算子
    modint<MOD> operator -(){return modint<MOD>(-val);}
    modint<MOD> operator +(const modint<MOD> &r) const { return modint<MOD>(*this) += r; }
    modint<MOD> operator -(const modint<MOD> &r) const { return modint<MOD>(*this) -= r; }
    modint<MOD> operator *(const modint<MOD> &r) const { return modint<MOD>(*this) *= r; }
    modint<MOD> operator /(const modint<MOD> &r) const { return modint<MOD>(*this) /= r; }

    // 代入演算子
    modint<MOD> &operator +=(const modint<MOD> &r){
        val += r.val;
        if(val >= MOD) val -= MOD;
        return *this;
    }
    modint<MOD> &operator -=(const modint<MOD> &r){
        if(val < r.val) val += MOD;
        val -= r.val;
        return *this;
    }
    modint<MOD> &operator *=(const modint<MOD> &r){
        val = val*r.val%MOD;
        if(val < 0) val += MOD;
        return *this;
    }
    modint<MOD> &operator /=(const modint<MOD> &r){
        *this *= inv(r);
        return *this;
    }

    //等価比較演算子
    bool operator ==(const modint<MOD>& r){return this -> val == r.val;}
    bool operator !=(const modint<MOD>& r){return this -> val != r.val;}
    bool operator <(const modint<MOD>& r){return this -> val < r.val;}
    bool operator <=(const modint<MOD>& r){return this -> val <= r.val;}
    bool operator >(const modint<MOD>& r){return this -> val > r.val;}
    bool operator >=(const modint<MOD>& r){return this -> val >= r.val;}

    // 累乗
    static modint<MOD> modpow(modint<MOD> num, ll exp){
        if(!exp) return modint<MOD>(1); // 0乗
        modint<MOD> ret(1);
        modint<MOD> tmp = num;
        while(exp){
            if(exp&1) ret *= tmp;
            tmp *= tmp;
            exp >>= 1;
        }
        return ret;
    }

    // 逆元
    static modint<MOD> inv(modint<MOD> num){
        return modpow(num, MOD-2);
    }

    // 階乗
    static modint<MOD> factorial(ll n){
        modint<MOD> ret(1);
        if(n == 0) return ret;
        if((ll)factorial_vec.size() >= n) return factorial_vec[n-1];
        ret = factorial(n-1)*n;
        factorial_vec.push_back(ret);
        return ret;
    }

    // コンビネーション
    static modint<MOD> combination(ll n, ll r){
        return factorial(n) / factorial(r) / factorial(n-r);
    }

};

using mint = modint<MOD>;
template <ll MOD> vector<modint<MOD>> modint<MOD>::factorial_vec;

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

#define MAX_V 200

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
    ll n,m;cin>>n>>m;
    vector<vector<ll>> h(n);
    rep(i,0,m){
        ll a,b;cin>>a>>b;
        a--;b--;
        h[a].push_back(b);
        h[b].push_back(a);
        add_edge(a+100,b,INF);
        add_edge(b+100,a,INF);
    }
    vector<ll> c(n);
    rep(i,0,n)cin>>c[i];
    rep(i,0,n) add_edge(i,i+100,c[i]);
    ll pre = max_flow(100,n-1);
    vector<ll> reach = mincut(100);
    vector<ll> ans;
    rep(i,0,n){
        if(reach[i] == 1 && reach[i+100]==0) ans.push_back(i+1);
    }
    cout<<pre<<endl;
    cout<<ans.size()<<endl;
    for(auto a:ans) cout<<a<<" ";
    cout<<endl;
    return 0;
}