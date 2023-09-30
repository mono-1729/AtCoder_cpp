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
	vector<vector<string>> v1(4);
	vector<vector<string>> v2(4);
	vector<vector<string>> v3(4);
	rep(i,0,4){
		string s;cin>>s;
		v1[0].push_back(s);
	}
	rep(i,0,4){
		string s;cin>>s;
		v2[0].push_back(s);
	}
	rep(i,0,4){
		string s;cin>>s;
		v3[0].push_back(s);
	}
	rep(x,0,3){
		rep(i,0,4){
			string s="";
			rep(j,0,4){
				s+=v1[x][j][3-i];
			}
			v1[x+1].push_back(s);
		}
	}
	rep(x,0,3){
		rep(i,0,4){
			string s="";
			rep(j,0,4){
				s+=v2[x][j][3-i];
			}
			v2[x+1].push_back(s);
		}
	}
	rep(x,0,3){
		rep(i,0,4){
			string s="";
			rep(j,0,4){
				s+=v3[x][j][3-i];
			}
			v3[x+1].push_back(s);
		}
	}
	vector<vector<int>> vv1(4);
	vector<vector<int>> vv2(4);
	vector<vector<int>> vv3(4);
	rep(i,0,4){
		rep(j,0,4){
			rep(k,0,4){
				
				if(v1[i][j][k]=='#'){
					vv1[i].push_back(j+k*4);
				}
				if(v2[i][j][k]=='#'){
					vv2[i].push_back(j+k*4);
				}
				if(v3[i][j][k]=='#'){
					vv3[i].push_back(j+k*4);
				}
			}
		}
	}
	bool ans=false;
	rep(i,0,4){
		rep(j,0,4){
			rep(k,0,4){
				rep(x,-16,16){
					rep(y,-16,16){
						rep(z,-16,16){
							bool flag=true;
							vector<int> field(16,0);
							for(auto a:vv1[i]){
								if(a/4+x/4<0 ||a%4+x%4<0 ||  a/4+x/4>=4 || a%4+x%4>=4 || field[a+x]==1){
									flag=false;
									break;
								}
								field[a+x]=1;
							}
							if(!flag)continue;
							for(auto a:vv2[j]){
								if(a/4+y/4<0 ||a%4+y%4<0 || a/4+y/4>=4 || a%4+y%4>=4 || field[a+y]==1){
									flag=false;
									break;
								}
								field[a+y]=1;
							}
							if(!flag)continue;
							for(auto a:vv3[k]){
								if(a/4+z/4<0 ||a%4+z%4<0 || a/4+z/4>=4 || a%4+z%4>=4 || field[a+z]==1){
									flag=false;
									break;
								}
								field[a+z]=1;
							}
							if(!flag)continue;
							rep(i,0,16){
								if(field[i]==0){
									flag=false;
									break;
								}
							}
							if(flag){
								ans=true;
								break;
							}
						}
					}
				}
			}
		}
	}
	if(ans){
		cout<<"Yes"<<endl;
	}else{
		cout<<"No"<<endl;
	}

	return 0;
}