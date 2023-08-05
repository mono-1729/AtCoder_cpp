#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
#define rep(i, a, n) for(int i = a; i < n; i++)
#define rrep(i, a, n) for(int i = a; i >= n; i--)
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
	if (n % 2 == 1) val *= x;
	return val % MOD;
}

vector<ll> fac(201);
void init_fac(){
	fac[0] = fac[1] = 1;
	rep(i, 2, 200){
		fac[i] = fac[i-1]*i%MOD;
	}
}

int main() {
	init_fac();
	int n;cin>>n;
	vector<int>w(n);
	rep(i,0,n)cin>>w[i];
	vector<vector<ll>>dp(1,vector<ll>(5001,0));
	int sum=0;
	dp[0][0]=1;
	ll ans=0;
	rep(i,0,n){
		sum+=w[i];
		vector<vector<ll>> dp2(i + 2, vector<long long>(5001, 0));
		rep(j,0,i+1){
			rep(k,0,min(sum+1,5001)) {
				if (dp[j][k]>0) dp2[j][k]+=dp[j][k];
				if(k+w[i]<5001) dp2[j+1][k+w[i]]+=dp[j][k];
				dp2[j][k]%=MOD;
				dp2[j+1][k]%=MOD;
			}
		}
		swap(dp, dp2);
	}
	if(sum%2==1){
		cout<<0<<endl;
		return 0;
	}
	rep(i,0,n){
		ans+=fac[i]*fac[n-i]%MOD*dp[i][sum/2]%MOD;
	}
	ans%=MOD;
	cout<<ans<<endl;
	return 0;
}