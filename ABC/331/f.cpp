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
template <ll MOD> class modint {
	ll val;
	static vector<modint<MOD>> factorial_vec;
public:
	ll get() const { return (ll)val; }
	// コンストラクタ
	modint(ll x = 0){
		val = x % MOD;
		if(val < 0) x += MOD;
	}

	// 入出力ストリーム
	friend constexpr istream &operator>>(istream &is, modint<MOD> &x){
		ll y; is >> y;
		x = y;
		return is;
	}
	friend constexpr ostream &operator<<(ostream &os, const modint<MOD> &x){
		return os << x.val;
	}

	// 算術演算子
	modint<MOD> operator -(){return modint<MOD>(-val);}
	modint<MOD> operator +(const modint<MOD> &r) const { return modint<MOD>(*this) += r; }
	modint<MOD> operator -(const modint<MOD> &r) const { return modint<MOD>(*this) -= r; }
	modint<MOD> operator *(const modint<MOD> &r) const { return modint<MOD>(*this) *= r; }
	modint<MOD> operator /(const modint<MOD> &r) const { return modint<MOD>(*this) /= r; }

	// 代入演算子
	modint<MOD> &operator +=(const modint<MOD> &r){
		val += r.val;
		if(val >= MOD) val -= MOD;
		return *this;
	}
	modint<MOD> &operator -=(const modint<MOD> &r){
		if(val < r.val) val += MOD;
		val -= r.val;
		return *this;
	}
	modint<MOD> &operator *=(const modint<MOD> &r){
		val = val*r.val%MOD;
		if(val < 0) val += MOD;
		return *this;
	}
	modint<MOD> &operator /=(const modint<MOD> &r){
		*this *= inv(r);
		return *this;
	}

	//等価比較演算子
	bool operator ==(const modint<MOD>& r){return this -> val == r.val;}
	bool operator !=(const modint<MOD>& r){return this -> val != r.val;}
	bool operator <(const modint<MOD>& r){return this -> val < r.val;}
	bool operator <=(const modint<MOD>& r){return this -> val <= r.val;}
	bool operator >(const modint<MOD>& r){return this -> val > r.val;}
	bool operator >=(const modint<MOD>& r){return this -> val >= r.val;}

	// 累乗
	static modint<MOD> modpow(modint<MOD> num, ll exp){
		if(!exp) return modint<MOD>(1); // 0乗
		modint<MOD> ret(1);
		modint<MOD> tmp = num;
		while(exp){
			if(exp&1) ret *= tmp;
			tmp *= tmp;
			exp >>= 1;
		}
		return ret;
	}

	// 逆元
	static modint<MOD> inv(modint<MOD> num){
		return modpow(num, MOD-2);
	}

	// 階乗
	static modint<MOD> factorial(ll n){
		modint<MOD> ret(1);
		if(n == 0) return ret;
		if((ll)factorial_vec.size() >= n) return factorial_vec[n-1];
		ret = factorial(n-1)*n;
		factorial_vec.push_back(ret);
		return ret;
	}

	// コンビネーション
	static modint<MOD> combination(ll n, ll r){
		return factorial(n) / factorial(r) / factorial(n-r);
	}

};

using mint = modint<MOD>;
template <ll MOD> vector<modint<MOD>> modint<MOD>::factorial_vec;

ll gcd(ll a, ll b){
	if(a%b == 0){
	  return b;
	}else{
	  return gcd(b, a%b);
	}
}

ll lcm(ll a, ll b){
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

template <typename X>
struct SegTree {
	using FX = function<X(X, X)>; // X•X -> X となる関数の型
	ll n;
	FX fx;
	const X ex;
	vector<X> dat;
	SegTree(ll n_, FX fx_, X ex_) : n(), fx(fx_), ex(ex_), dat(n_ * 4, ex_) {
		ll x = 1;
		while (n_ > x) {
			x *= 2;
		}
		n = x;
	}
	void set(ll i, X x) { dat[i + n - 1] = x; }
	void build() {
		for (ll k = n - 2; k >= 0; k--) dat[k] = fx(dat[2 * k + 1], dat[2 * k + 2]);
	}
	void update(ll i, X x) {
		i += n - 1;
		dat[i] = x;
		while (i > 0) {
			i = (i - 1) / 2;  // parent
			dat[i] = fx(dat[i * 2 + 1], dat[i * 2 + 2]);
		}
	}
	X query(ll a, ll b) { return query_sub(a, b, 0, 0, n); }
	X query_sub(ll a, ll b, ll k, ll l, ll r) {
		if (r <= a || b <= l) {
			return ex;
		} else if (a <= l && r <= b) {
			return dat[k];
		} else {
			X vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
			X vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
			return fx(vl, vr);
		}
	}
};


constexpr int B = 5;
int mod[B] = {998244353, 1000000007, 1000000009, 1000000021, 1000000033};
int base[B];
struct Hash {
  long long h1, pw;
};
using T = array<Hash, B>;
T op(T lhs, T rhs) {
  T res;
  for (int i = 0; i < B; i++) {
    res[i].h1 = (lhs[i].h1 * rhs[i].pw + rhs[i].h1) % mod[i];
    res[i].pw = lhs[i].pw * rhs[i].pw % mod[i];
  }
  return res;
}
T e() {
  T res;
  for (int i = 0; i < B; i++) res[i] = {0, 1};
  return res;
}
T gen(char c) {
  T res;
  for (int i = 0; i < B; i++) res[i].h1 = c, res[i].pw = base[i];
  return res;
}

int main() {
	mt19937_64 rng(time(0));
	for (int i = 0; i < B; i++) base[i] = rng() % mod[i];
	ll n,q;cin>>n>>q;
	string s;cin>>s;
	vector<T> init1(n),init2(n);
	for (int i = 0; i < n; i++){
		init1[i] = gen(s[i]);
		init2[n-i-1] = gen(s[i]);
	}
	SegTree<T> seg1(init1.size(), op, e());
	SegTree<T> seg2(init2.size(), op, e());
	for(int i = 0; i < n; i++){
		seg1.set(i, init1[i]);
		seg2.set(i, init2[i]);
	}
	seg1.build();
	seg2.build();
	while(q--){
		ll type;cin>>type;
		if(type==1){
			ll l;char c;cin>>l>>c;
			l--;
			seg1.update(l, gen(c));
			seg2.update(n-l-1, gen(c));
		}
		else{
			ll l,r;cin>>l>>r;
			l--;
			bool ok = true;
			for (int i = 0; i < B; i++) {
				ok &= seg1.query(l, r)[i].h1 == seg2.query(n-r, n-l)[i].h1;
			}
			if(ok)cout<<"Yes"<<endl;
			else cout<<"No"<<endl;
		}
	}
	return 0;
}