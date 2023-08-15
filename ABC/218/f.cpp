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
	val %= MOD;
	if (n % 2 == 1) val *= x;
	return val % MOD;
}

int main() {
	int t;cin>>t;
	rep(turn,0,t){
		int n;cin>>n;
		vector<set<int>>g(n);
		rep(i,0,n-1){
			int a,b;cin>>a>>b;
			a--;b--;
			g[a].insert(b);
			g[b].insert(a);
		}
		string s;cin>>s;
		queue<int>q;
		vector<int>color(n);
		vector<char>ans(n,'n');
		rep(i,0,n){
			if(g[i].size() == 1){
				q.push(i);
			}
		}
		bool ok = true;
		while(true){
			int pos=q.front();q.pop();
			if(g[pos].size() == 0) {
				if(color[pos] >=0 && s[pos]=='W') ok = false;
				if(color[pos] <=0 && s[pos]=='B') ok = false;
				if(ans[pos]=='n') ans[pos]='W';
				break;
			}
			int par=*g[pos].begin();
			if(s[pos]=='W'){
				if(color[pos]>0) {
					ok = false;
					break;
				}
				if(color[pos]==0) {
					if (ans[par]=='n'){
						ans[par]='W';
					}
					else if(ans[par]=='B'){
						ok = false;
						break;
					}
				}
			}
			if(s[pos]=='B'){
				if(color[pos]<0) {
					ok = false;
					break;
				}
				if(color[pos]==0) {
					if (ans[par]=='n'){
						ans[par]='B';
					}
					else if(ans[par]=='W'){
						ok = false;
						break;
					}
				}
			}
			if(ans[pos]=='n') ans[pos]=s[par];
			if(ans[pos] == 'W') color[par] -=1;
			else color[par] += 1;
			g[par].erase(pos);
			g[pos].erase(par);
			if(g[par].size() <= 1) q.push(par);
		}
		if(ok){
			rep(i,0,n) cout<<ans[i];
			cout<<endl;
		}
		else{
			//rep(i,0,n) cout<<ans[i];
			//rep(i,0,n) cout<<color[i];
			cout<<-1<<endl;
		}
	}
	return 0;
}