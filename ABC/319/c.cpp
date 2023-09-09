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
	vector<vector<int>> c(3, vector<int>(3));
	rep(i,0,3){
		rep(j,0,3){
			cin>>c[i][j];
		}
	}
	vector<vector<pii>>x(9);
	if(c[0][1]==c[0][2])x[0].push_back({1,2});
	if(c[1][1]==c[2][2])x[0].push_back({4,8});
	if(c[1][0]==c[2][0])x[0].push_back({3,6});

	if(c[1][1]==c[2][1])x[1].push_back({4,7});
	if(c[0][0]==c[0][2])x[1].push_back({0,2});

	if(c[0][0]==c[0][1])x[2].push_back({0,1});
	if(c[1][2]==c[2][2])x[2].push_back({5,8});
	if(c[1][1]==c[2][0])x[2].push_back({4,6});

	if(c[0][0]==c[2][0])x[3].push_back({0,6});
	if(c[1][1]==c[1][2])x[3].push_back({4,5});

	if(c[1][0]==c[1][2])x[4].push_back({3,5});
	if(c[0][1]==c[2][1])x[4].push_back({1,7});
	if(c[0][0]==c[2][2])x[4].push_back({0,8});
	if(c[0][2]==c[2][0])x[4].push_back({2,6});

	if(c[0][2]==c[2][2])x[5].push_back({2,8});
	if(c[1][0]==c[1][1])x[5].push_back({3,4});

	if(c[2][1]==c[2][2])x[6].push_back({7,8});
	if(c[1][1]==c[0][2])x[6].push_back({4,2});
	if(c[1][0]==c[0][0])x[6].push_back({3,0});

	if(c[1][1]==c[0][1])x[7].push_back({4,1});
	if(c[2][0]==c[2][2])x[7].push_back({6,8});

	if(c[2][0]==c[2][1])x[8].push_back({6,7});
	if(c[1][2]==c[0][2])x[8].push_back({5,2});
	if(c[1][1]==c[0][0])x[8].push_back({4,0});
	vector<int>num(9);
	rep(i,0,9)num[i]=i;
	int ans=0;
	do{
		bool flg=true;
		vector<vector<int>> check(3, vector<int>(3,0));
		rep(i,0,9){
			for(auto j:x[num[i]]){
				if(check[j.first/3][j.first%3]==1 && check[j.second/3][j.second%3]==1)flg=false;
			}
			check[num[i]/3][num[i]%3]=1;
		}
		if(flg)ans++;
	}while(next_permutation(num.begin(), num.end()));
	double p=ans/362880.0000;
	cout<<fixed<<setprecision(10)<<p<<endl;
	return 0;
}