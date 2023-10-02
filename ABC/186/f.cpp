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

template <typename X>
struct SegTree {
	using FX = function<X(X, X)>; // X•X -> X となる関数の型
	int n;
	FX fx;
	const X ex;
	vector<X> dat;
	SegTree(int n_, FX fx_, X ex_) : n(), fx(fx_), ex(ex_), dat(n_ * 4, ex_) {
		int x = 1;
		while (n_ > x) {
			x *= 2;
		}
		n = x;
	}
	void set(int i, X x) { dat[i + n - 1] = x; }
	void build() {
		for (int k = n - 2; k >= 0; k--) dat[k] = fx(dat[2 * k + 1], dat[2 * k + 2]);
	}
	void update(int i, X x) {
		i += n - 1;
		dat[i] = x;
		while (i > 0) {
			i = (i - 1) / 2;  // parent
			dat[i] = fx(dat[i * 2 + 1], dat[i * 2 + 2]);
		}
	}
	X query(int a, int b) { return query_sub(a, b, 0, 0, n); }
	X query_sub(int a, int b, int k, int l, int r) {
		if (r <= a || b <= l) {
			return ex;
		} else if (a <= l && r <= b) {
			return dat[k];
		} else {
			X vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
			X vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
			return fx(vl, vr);
		}
	}
};

auto fx = [](int x1, int x2) -> int { return x1+x2; };
int ex = 0;

int main() {
	ll h,w,m;cin>>h>>w>>m;
	vector<ll> minx(w,h), miny(h,w);
	vector<vector<ll>> xy(h);
	rep(i,0,m){
		ll a,b;cin>>a>>b;
		a--;b--;
		chmin(minx[b], a);
		chmin(miny[a], b);
		xy[a].push_back(b); 
	}
	SegTree<int> seg(w, fx, ex);
	ll ans=0;
	rep(i,0,miny[0]){
		ans+=minx[i];
	}
	rep(i,miny[0],w){
		seg.update(i, 1);
	}
	rep(i,0,minx[0]){
		ans+=seg.query(0, miny[i]);
		for(auto y:xy[i]){
			seg.update(y, 1);
		}
	}
	cout<<ans<<endl;
	return 0;
}