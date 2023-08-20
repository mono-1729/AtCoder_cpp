#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
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

vector<set<int>> g(200005);
vector<set<int>>in(200005),out(200005);
vector<int> d(200005), f(200005);

int cnt = 1;
void dfs(int pos){
    d[pos] = cnt;
    cnt++;
    for(auto npos: g[pos]){
		out[pos].insert(npos);
		in[npos].insert(pos);
        if(d[npos] == 0) {
			dfs(npos);
		}
    }
}

int main() {
	int n;cin>>n;
	rep(i,0,n){
		int c;cin>>c;
		rep(j,0,c){
			int a;cin>>a;
			a--;
			g[i].insert(a);
		}
	}
	vector<int> ans(n);
	dfs(0);
	queue<int> q;
	rep(i,0,n){
		//cout<<i<<" "<<in[i].size()<<" "<<out[i].size()<<endl;
		if(out[i].size() == 0 && in[i].size() != 0){
			q.push(i);
		}
	}
	while(!q.empty()){
		int pos = q.front();q.pop();
		ans.push_back(pos);
		for(auto npos: in[pos]){
			//cout<<pos<<" "<<npos<<" tes"<<endl;
			out[npos].erase(pos);
			if(out[npos].size() == 0 && in[npos].size() != 0){
				q.push(npos);
			}
		}
		in[pos].clear();
	}
	for(auto a: ans){
		if(a == 0) continue;
		cout<<a+1<<" ";
	}
	cout<<endl;
	return 0;
}