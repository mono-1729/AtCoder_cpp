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

class UnionFind {
	vector<ll> parent, maxi, mini;
	inline ll root(ll n){
		return (parent[n] < 0? n:parent[n] = root(parent[n]));
	}
public:
	UnionFind(ll n_ = 1): parent(n_, -1), maxi(n_), mini(n_){
		iota(maxi.begin(), maxi.end(), 0);
		iota(mini.begin(), mini.end(), 0);
	}

	inline bool same(ll x, ll y){
		return root(x) == root(y);
	}

	inline void unite(ll x, ll y){
		ll rx = root(x);
		ll ry = root(y);
		if(rx == ry) return;
		if(parent[rx] > parent[ry]) swap(rx, ry);
		parent[rx] += parent[ry];
		parent[ry] = rx;
		maxi[x] = std::max(maxi[x],maxi[y]);
		mini[x] = std::min(mini[x],mini[y]);
	}

	inline ll min(ll x){
		return mini[root(x)];
	}

	inline ll max(int x){
		return mini[root(x)];
	}

	inline ll size(ll x){
		return (-parent[root(x)]);
	}

	inline ll operator[](ll x){
		return root(x);
	}

	inline void print(){
		rep(i, 0, (ll)parent.size()) cout << root(i) ;
		cout << endl;
	}

	void clear(){
		rep(i, 0, (ll)parent.size()){
			parent[i] = -1;
		}
		iota(maxi.begin(), maxi.end(), 0);
		iota(mini.begin(), mini.end(), 0);
	}
};

int main() {
	ll n,m;cin>>n>>m;
	vector<ll> x(n),y(n),a(m),b(m),z(m);
	vector<tuple<ll,ll,ll>> e;
	rep(i,0,n){
		cin>>x[i];
		e.push_back(make_tuple(x[i],i,n));
	}
	rep(i,0,n){
		cin>>y[i];
		e.push_back(make_tuple(y[i],i,n+1));
	}
	rep(i,0,m){
		cin>>a[i]>>b[i]>>z[i];
		a[i]--;b[i]--;
		e.push_back(make_tuple(z[i],a[i],b[i]));
	}
	sort(e.begin(),e.end());
	ll ans=INF;
	rep(i,0,4){
		ll possum=n+(i/2)+(i%2);
		bool useair=(i/2);
		bool useport=(i%2);
		UnionFind uf(n+2);
		ll cost=0;
		for(auto [zz,aa,bb]:e){
			if(!useair && bb==n)continue;
			if(!useport && bb==n+1)continue;
			if(uf.same(aa,bb))continue;
			uf.unite(aa,bb);
			cost+=zz;
		}
		if(uf.size(0)!=possum)continue;
		chmin(ans,cost);
	}
	cout<<ans<<endl;
	return 0;
}