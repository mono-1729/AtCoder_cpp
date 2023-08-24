#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
constexpr ll MOD = 1000000007;
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
typedef ModInt<1000000007> mint;

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
int maxnum=3000005;
vector<ll> fac(maxnum), inv(maxnum), finv(maxnum);
void init_fac(){
	fac[0] = fac[1] = 1;
	inv[1] = 1;
	finv[0] = finv[1] = 1;
	rep(i, 2, maxnum){
		fac[i] = fac[i-1]*i%MOD;
		inv[i] = MOD-MOD/i*inv[MOD%i]%MOD;
		finv[i] = finv[i-1]*inv[i]%MOD;
	}
}
ll nCr(ll n, ll r){
	if(n < 0 or n-r < 0 or r < 0) return 0;
	return fac[n]*(finv[n-r]*finv[r]%MOD)%MOD;
}
ll nHr(ll n, ll r){
	return nCr(n+r-1, r);
}

mint dp[2010101];
mint g(int R, int C) {
    dp[0] = 1;
    int r1 = 0, c1 = 0;
    int r2 = 0, c2 = 0;
    rep(rc, 0, R + C) {
        dp[rc + 1] = dp[rc] * 2;

        if (r1 != R) r1++;
        else {
            dp[rc + 1] -= nCr(r1 + c1, r1);
            c1++;
        }

        if (c2 != C) c2++;
        else {
            dp[rc + 1] -= nCr(r2 + c2, r2);
            r2++;
        }
    }
    mint res = 0;
    rep(rc, 0, R + C + 1) res += dp[rc];
    return res;
}

int main() {
	init_fac();
	int r1,c1,r2,c2; cin>>r1>>c1>>r2>>c2;

	mint ans = g(r2, c2) - g(r1 - 1, c2) - g(r2, c1 - 1) + g(r1 - 1, c1 - 1);
    cout << ans << endl;
	return 0;
}