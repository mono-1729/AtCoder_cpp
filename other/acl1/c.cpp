#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
constexpr ll mod = 1000000007;
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

#define MAX_V 5005

struct edge {
	ll to, cap, cost, rev;
	edge(ll to, ll cap, ll cost, ll rev) : to(to), cap(cap), cost(cost), rev(rev) {}
};

ll V=MAX_V;
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
		fill(dist, dist + V, INF);
		dist[s] = 0;
		bool update = true;
		while(update) {
			update = false;
			rep(v, 0, V) {
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
	ll n,m;cin>>n>>m;
	vector<string> s(n);
	rep(i,0,n) cin>>s[i];
	rep(i,0,n*m) add_edge(100+i,5000,1,10000-(i%m)-(i/m));
	vector<ll> dx={1,0},dy={0,1};
	ll cnt=0;
	ll ans=0;
	rep(i,0,n)rep(j,0,m){
		if(s[i][j]=='o'){
			add_edge(4999,cnt,1,0);
			ans+=10000-i-j;
			vector<vector<ll>> dis(n,vector<ll>(m,-1));
			queue<pll> que;
			que.push({i,j});
			dis[i][j]=0;
			while(!que.empty()){
				ll x,y;tie(x,y)=que.front();que.pop();
				add_edge(cnt,100+x*m+y,1,0);
				rep(k,0,2){
					ll nx=x+dx[k],ny=y+dy[k];
					if(nx<0||nx>=n||ny<0||ny>=m) continue;
					if(s[nx][ny]!='#'&&dis[nx][ny]==-1){
						dis[nx][ny]=dis[x][y]+1;
						que.push({nx,ny});
					}
				}
			}
			cnt++;
		}
	}
	ans-=min_cost_flow(4999,5000,cnt);
	cout<<ans<<endl;
	return 0;
}