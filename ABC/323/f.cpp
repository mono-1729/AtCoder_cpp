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

int main() {
	ll xa, ya, xb, yb, xc, yc;
	cin >> xa >> ya >> xb >> yb >> xc >> yc;
	xc -= xa;
	yc -= ya;
	xb -= xa;
	yb -= ya;
	if(xb==0){
		swap(xb,yb);
		swap(xc,yc);
	}
	if(yb<0){
		yb *= -1;
		yc *= -1;
	}
	if(xb<0){
		xb *= -1;
		xc *= -1;
	}
	xc -= xb;
	yc -= yb;
	ll ans=0;
	if(yb==0){
		if(xc>0 && yc==0) ans = abs(xb)+abs(yb)+abs(xc)+abs(yc)-1;
		else if(xc<0 && yc==0) ans = abs(xb)+abs(yb)+abs(xc)+abs(yc)+3;
		else if(xc==0) ans = abs(xb)+abs(yb)+abs(xc)+abs(yc)+1;
		else if(xc>0) ans = abs(xb)+abs(yb)+abs(xc)+abs(yc)+1;
		else if(xc<0) ans = abs(xb)+abs(yb)+abs(xc)+abs(yc)+3;
	}
	else{
		if(xc<0 && yc<0) ans = abs(xb)+abs(yb)+abs(xc)+abs(yc)+3;
		else if(xc>0 && yc==0) ans = abs(xb)+abs(yb)+abs(xc)+abs(yc)-1;
		else if(xc==0 && yc>0) ans = abs(xb)+abs(yb)+abs(xc)+abs(yc)-1;
		else ans = abs(xb)+abs(yb)+abs(xc)+abs(yc)+1;
	}
	// cout<<xa<<" "<<ya<<" "<<xb<<" "<<yb<<" "<<xc<<" "<<yc<<endl;
	cout << ans << endl;
	return 0;
}