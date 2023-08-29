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

/*
中国剰余定理 :
    m1とm2を互いに素な正の整数とする。
        x ≡ b1 (mod. m1)
        x ≡ b2 (mod. m2)
    を満たす整数 x が 0 以上 m1, m2 未満にただ1つ存在する。

    特にそれをｒとすると
        x ≡ b1 (mod. m1), x ≡ b2 (mod. m2)
        ↔ x ≡ r (mod. m1m2)
    が成立する。

アルゴリズム : 
二元の場合 : 
    x ≡ b1 (mod. m1), x ≡ b2 (mod. m2) の場合を解く。
    d = gcd(m1, m2) として、拡張ユークリッドの互除法によって
    m1*p+m2*q = d を満たす (p, q) を求め、
    x = b1+m1((b2-b1)/d)*p とすればよい。
    ( 
        b1 = b2 (mod. gcd(m1, m2)) より、b2-b1はdで割り切れる。
        s = ((b2-b1)/d) とおくと、m1*p+m2*q = d より、 
        s*m1*p+s*m2*q = b2-b1 
        →　s*m1*p+b1 = -s*m2*q+b2     
        x=b1+s*m1*p(=b2−s*m2*q) とおくと、
        x ≡ b1 (mod. m1), x ≡ b2 (mod. m2) が成り立っていることが分かる。
    )
*/

// 2元の場合
// 負の数にも対応した mod 
inline ll mod(ll a, ll m) {
    return (a % m + m) % m;
}

inline long long mul(long long a, long long b, long long m) {
    a = mod(a, m); b = mod(b, m);
    if (b == 0) return 0;
    long long res = mul(mod(a + a, m), b>>1, m);
    if (b & 1) res = mod(res + a, m);
    return res;
}

// 拡張ユークリッドの互除法
// ap+bq=gcd(a, b) となる (p, q) を求め、d = gcd(a, b) をリターンします。
ll extGCD(ll a, ll b, ll &p, ll &q){
    if (b == 0) {
        p = 1;
        q = 0;
        return a;
    }
    ll d = extGCD(b, a%b, q, p);
    q -= a/b*p;
    return d;
}

// 中国剰余定理
// リターン値を (r, m) とすると解は x = r (mod. m)
// 解なしの場合は (0, -1) をリターン
pll chineseRem(const vector<ll> &b, const vector<ll> &m){
    ll r = 0, M = 1;
    rep(i, 0, (int)b.size()){
        ll p, q;
        ll d = extGCD(M, m[i], p, q); // p is inv of m1/d (mod. m[i]/d)
        if((b[i] - r) % d != 0) return {0, -1};
        ll tmp = mul(((b[i] - r) / d), p, (m[i] / d));
        r += M * tmp;
        M *= m[i] / d;
    }
    return {mod(r, M), M};
}

int main(){
    ll n;cin>>n;
	vector<ll>nums;
	ll ans=INF;
	rep(i,1,sqrt(n*2)+1){
		if((n*2)%i==0){
			nums.push_back(i);
			nums.push_back((n*2)/i);
		}
	}
	for(auto num:nums){
		if(gcd(num, (n*2)/num)!=1)continue;
		ll x=chineseRem({0,(n*2)/num-1},{num,(n*2)/num}).first;
		if(x==0)continue;
		chmin(ans,chineseRem({0,(n*2)/num-1},{num,(n*2)/num}).first);
		//cout<<num<<" "<<chineseRem({0,(n*2)/num-1},{num,(n*2)/num}).first<<endl;
	}
	cout<<ans<<endl;
    return 0;
}