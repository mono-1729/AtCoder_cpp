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
	int h,w;cin>>h>>w;
	vector<vector<int>>a(h+1, vector<int>(w,2));
	rep(i,1,h+1){
		rep(j,0,w){
			cin>>a[i][j];
		}
	}
	vector<vector<vector<int>>>dp(h+2, vector<vector<int>>(2, vector<int>(2,IINF)));
	dp[0][0][0]=0;
	rep(i,0,h){
		rep(j,0,2){
			rep(k,0,2){
				if (dp[i][j][k]==IINF) continue;
				if (i==0){
					dp[i+1][0][j]=min(dp[i+1][0][j], dp[i][j][k]);
					dp[i+1][1][j]=min(dp[i+1][1][j], dp[i][j][k]+1);
					continue;
				}
				bool flag=true;
				rep(l,0,w){
					bool flag2=false;
					if(l>0 && a[i][l]==a[i][l-1]) flag2=true;
					if(l<w-1 && a[i][l]==a[i][l+1]) flag2=true;
					if(i>1 && j==k){
						if(a[i][l]==a[i-1][l]) flag2=true;
					}
					if(i>1 && j!=k){
						if(a[i][l]==1-a[i-1][l]) flag2=true;
					} 
					if(j==0){
						if(a[i][l]==a[i+1][l]) flag2=true;
					}
					if(j==1){
						if(a[i][l]==1-a[i+1][l]) flag2=true;
					} 
					if(flag2==false) flag=false;
				}
				if (flag) dp[i+1][0][j]=min(dp[i+1][0][j], dp[i][j][k]);
				flag=true;
				rep(l,0,w){
					bool flag2=false;
					if(l>0 && a[i][l]==a[i][l-1]) flag2=true;
					if(l<w-1 && a[i][l]==a[i][l+1]) flag2=true;
					if(i>1 && j==k){
						if(a[i][l]==a[i-1][l]) flag2=true;
					}
					if(i>1 && j!=k){
						if(a[i][l]==1-a[i-1][l]) flag2=true;
					} 
					if(j==1){
						if(a[i][l]==a[i+1][l]) flag2=true;
					}
					if(j==0){
						if(a[i][l]==1-a[i+1][l]) flag2=true;
					} 
					if(flag2==false) flag=false;
				}
				if (flag) dp[i+1][1][j]=min(dp[i+1][1][j], dp[i][j][k]+1);
			}
		}
	}
	int ans=IINF;
	rep(i,0,2){
		rep(j,0,2){
			bool flag=true;
			rep(k,0,w){
				bool flag2=false;
				if(k>0 && a[h][k]==a[h][k-1]) flag2=true;
				if(k<w-1 && a[h][k]==a[h][k+1]) flag2=true;
				if(i==j && a[h][k]==a[h-1][k]) flag2=true;
				if(i!=j && a[h][k]==1-a[h-1][k]) flag2=true;
				if(flag2==false) flag=false;
			}
			if(flag) ans=min(ans, dp[h][i][j]);
		}
	}
	// rep(i,0,h+1){
	// 	rep(j,0,2){
	// 		rep(k,0,2){
	// 			cout<<dp[i][j][k]<<" ";
	// 		}
	// 	}
	// 	cout<<endl;
	// }
	if (ans==IINF) cout<<-1<<endl;
	else cout<<ans<<endl;
	return 0;
}