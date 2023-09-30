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
	ll n,k,p;cin>>n>>k>>p;
	vector<ll> c(n);
	vector<vector<ll>>a(n, vector<ll>(k));
	rep(i,0,n){
		cin>>c[i];
		rep(j,0,k) cin>>a[i][j];
	}
	vector<vector<ll>> dp(n+1, vector<ll>(powMod(p+1,k), INF));
	dp[0][0]=0;
	rep(i,0,n){
		rep(j,0,powMod(p+1,k)){
			ll tmp=j;
			vector<ll> b(k, 0);
			rep(l,0,k){
				b[l]=tmp%(p+1);
				tmp/=(p+1);
			}
			rep(l,0,k){
				int x=b[l]+a[i][l];
				b[l]=min((int)p, x);	
			}
			int index=0;
			rep(l,0,k){
				index+=powMod((p+1),l)*b[l];
			}
			rep(l,0,k){
				dp[i+1][j]=min(dp[i+1][j], dp[i][j]);
				dp[i+1][index]=min(dp[i+1][index], dp[i][j]+c[i]);
			}
			
		}
	}
	if(dp[n][powMod((p+1),k)-1]==INF){
		cout<<-1<<endl;
	}else{
		cout<<dp[n][powMod((p+1),k)-1]<<endl;
	}
	// rep(i,0,powMod((p+1),k)){
	// 	if(dp[n][i]!=INF)cout<<dp[n][i]<<" "<<i<<endl;
	// }
	return 0;
}