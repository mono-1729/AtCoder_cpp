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

int main() {
	ll n,k;cin>>n>>k;
	vector<ll> a(n);
	vector<vector<ll>> index(200006);
	rep(i,0,n){
		cin>>a[i];
		index[a[i]].push_back(i);
	}
	vector<ll> time(n,-1);
	pll pre={0,-1};
	rep(_,0,n+1){
		ll id=(pre.second+1)%n,num=a[id];
		pll pos =pre;
		if(pre.second==n-1) pos.first++;
		if(index[num].back()==id){
			pos.first++;
			pos.second=index[num][0];
		}else{
			pos.second=index[num][upper_bound(index[num].begin(),index[num].end(),id)-index[num].begin()];
		}
		if(pos.first>=k) break;
		if(time[id]!=-1){            
			pos.first+=((k-pos.first-1)/(pos.first-time[id]))*(pos.first-time[id]);
			pre=pos;
			break;
		} 
		time[id]=pos.first;
		pre=pos;
	}
	rep(_,0,n+1){
		ll id=(pre.second+1)%n,num=a[id];
		pll pos =pre;
		if(pre.second==n-1) pos.first++;
		if(index[num].back()==id){
			pos.first++;
			pos.second=index[num][0];
		}else{
			pos.second=index[num][upper_bound(index[num].begin(),index[num].end(),id)-index[num].begin()];
		}
		if(pos.first>=k)break;
		pre=pos;
	}
	if(pre.second==n-1) pre.first++;
	pre.second=(pre.second+1)%n;
	if(pre.first>=k) return 0;
	vector<int>ans;
	vector<int>used(200005,-1);
	rep(i,pre.second,n){
		if(used[a[i]]==-1){
			used[a[i]]=1;
			ans.push_back(a[i]);
		}
		else{
			while(true){
				ll tmp=ans.back();
				ans.pop_back();
				used[tmp]=-1;
				if(tmp==a[i]) break;
			}
		}
	}
	for(auto x:ans)cout<<x<<" ";
	cout<<endl;
	return 0;
}