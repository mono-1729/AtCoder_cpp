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

int main() {
	int n;cin>>n;
	vector<vector<vector<int>>>num(100,vector<vector<int>>(100,vector<int>(100,0)));
	vector<set<int>>nextto(n);
	rep(ii,0,n){
		int x1,y1,z1,x2,y2,z2; cin>>x1>>y1>>z1>>x2>>y2>>z2;
		rep(i,x1,x2){
			rep(j,y1,y2){
				rep(k,z1,z2){
					num[i][j][k]=ii+1;
				}
			}
		}
	}
	rep(i,0,100){
		rep(j,0,100){
			rep(k,0,100){
				if (num[i][j][k]==0) continue;
				if (i!=0){
					if(num[i-1][j][k]!=0 && num[i-1][j][k]!=num[i][j][k]){
						nextto[num[i][j][k]-1].insert(num[i-1][j][k]-1);
						nextto[num[i-1][j][k]-1].insert(num[i][j][k]-1);
					} 
				}
				if (i!=99){
					if(num[i+1][j][k]!=0 && num[i+1][j][k]!=num[i][j][k]){
						nextto[num[i][j][k]-1].insert(num[i+1][j][k]-1);
						nextto[num[i+1][j][k]-1].insert(num[i][j][k]-1);
					} 
				}
				if (j!=0){
					if(num[i][j-1][k]!=0 && num[i][j-1][k]!=num[i][j][k]){
						nextto[num[i][j][k]-1].insert(num[i][j-1][k]-1);
						nextto[num[i][j-1][k]-1].insert(num[i][j][k]-1);
					} 
				}
				if (j!=99){
					if(num[i][j+1][k]!=0 && num[i][j+1][k]!=num[i][j][k]){
						nextto[num[i][j][k]-1].insert(num[i][j+1][k]-1);
						nextto[num[i][j+1][k]-1].insert(num[i][j][k]-1);
					} 
				}
				if (k!=0){
					if(num[i][j][k-1]!=0 && num[i][j][k-1]!=num[i][j][k]){
						nextto[num[i][j][k]-1].insert(num[i][j][k-1]-1);
						nextto[num[i][j][k-1]-1].insert(num[i][j][k]-1);
					} 
				}
				if (k!=99){
					if(num[i][j][k+1]!=0 && num[i][j][k+1]!=num[i][j][k]){
						nextto[num[i][j][k]-1].insert(num[i][j][k+1]-1);
						nextto[num[i][j][k+1]-1].insert(num[i][j][k]-1);
					} 
				}
			}
		}
	}
	rep(i,0,n) cout<<nextto[i].size()<<endl;
	return 0;
}