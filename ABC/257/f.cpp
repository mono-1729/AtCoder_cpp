#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}
template<int MOD> struct ModInt {
	static const int Mod = MOD; unsigned x; ModInt() : x(0) { }
	ModInt(signed sig) { x = sig < 0 ? sig % MOD + MOD : sig % MOD; }
	ModInt(signed long long sig) { x = sig < 0 ? sig % MOD + MOD : sig % MOD; }
	int get() const { return (int)x; }
	ModInt &operator+=(ModInt that) { if ((x += that.x) >= MOD) x -= MOD; return *this; }
	ModInt &operator-=(ModInt that) { if ((x += MOD - that.x) >= MOD) x -= MOD; return *this; }
	ModInt &operator*=(ModInt that) { x = (unsigned long long)x * that.x % MOD; return *this; }
	ModInt &operator/=(ModInt that) { return *this *= that.inverse(); }
	ModInt operator+(ModInt that) const { return ModInt(*this) += that; }
	ModInt operator-(ModInt that) const { return ModInt(*this) -= that; }
	ModInt operator*(ModInt that) const { return ModInt(*this) *= that; }
	ModInt operator/(ModInt that) const { return ModInt(*this) /= that; }
	ModInt inverse() const { long long a = x, b = MOD, u = 1, v = 0;
		while (b) { long long t = a / b; a -= t * b; std::swap(a, b); u -= t * v; std::swap(u, v); }
		return ModInt(u); }
	bool operator==(ModInt that) const { return x == that.x; }
	bool operator!=(ModInt that) const { return x != that.x; }
	ModInt operator-() const { ModInt t; t.x = x == 0 ? 0 : Mod - x; return t; }
};
template<int MOD> ostream& operator<<(ostream& st, const ModInt<MOD> a) { st << a.get(); return st; };
template<int MOD> ModInt<MOD> operator^(ModInt<MOD> a, unsigned long long k) {
	ModInt<MOD> r = 1; while (k) { if (k & 1) r *= a; a *= a; k >>= 1; } return r; }
typedef ModInt<998244353> mint;

int gcd(int a, int b){
	if(a%b == 0){
	  return b;
	}else{
	  return gcd(b, a%b);
	}
}

int lcm(int a, int b){
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

int main() {
	int n,m;cin>>n>>m;
	vector<vector<int>> g(n);
	vector<ll> ver,dist0(n,INF),distn(n,INF);
	rep(i,0,m){
		int u,v;cin>>u>>v;
		if(u==0) ver.push_back(v-1);
		else {
			u--;v--;
			g[u].push_back(v);
			g[v].push_back(u);
		}
	}
	queue<int> q;
	q.push(0);
	dist0[0]=0;
	while(!q.empty()){
		int v=q.front();q.pop();
		for(auto nv:g[v]){
			if(dist0[nv]==INF){
				dist0[nv]=dist0[v]+1;
				q.push(nv);
			}
		}
	}
	q.push(n-1);
	distn[n-1]=0;
	while(!q.empty()){
		int v=q.front();q.pop();
		for(auto nv:g[v]){
			if(distn[nv]==INF){
				distn[nv]=distn[v]+1;
				q.push(nv);
			}
		}
	}
	ll mind0=INF,mindn=INF;
	for(auto v:ver){
		chmin(mind0,dist0[v]);
		chmin(mindn,distn[v]);
	}
	rep(i,0,n){
		ll ans=dist0[n-1];
		chmin(ans,min(dist0[i],mind0+1)+min(distn[i],mindn+1));
		if(ans==INF) cout<<-1<<" ";
		else cout<<ans<<" ";
	}
	cout<<endl;

	return 0;
}