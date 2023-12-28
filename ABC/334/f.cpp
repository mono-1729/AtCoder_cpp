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

template <class T, T (*op)(T, T), T (*e)(), class F, T (*mapping)(F, T), F (*composition)(F, F), F (*id)()> 
class LazySegmentTree {
	ll _n, size, log;
	vector<T> d;
	vector<F> lz;

	void update(ll k) { d[k] = op(d[2 * k], d[2 * k + 1]); }

	void all_apply(ll k, F f){
		d[k] = mapping(f, d[k]);
		if (k < size) lz[k] = composition(f, lz[k]);
	}

	void push(ll k){
		all_apply(2*k, lz[k]);
		all_apply(2*k+1, lz[k]);
		lz[k] = id();
	}

public:
	LazySegmentTree() : LazySegmentTree(0) {}
	explicit LazySegmentTree(ll n) : LazySegmentTree(vector<T>(n, e())) {} // explicit で明示的に型を指定する
	explicit LazySegmentTree(const vector<T> &v) : _n(int(v.size())) {
		// sizeは_nを超える最小の2のべき乗
		size = 1;
		while(size < _n) size *= 2, log++; 

		// log は木の高さ（sizeの桁数）
		log = 0;
		while (!(size & (1 << log))) log++;

		d = vector<T>(2*size, e());
		lz = vector<F>(size, id());

		for(ll i = 0; i < _n; i++) d[size+i] = v[i];
		for(ll i = size-1; i >= 1; i--){
			update(i);
		}
	}

	void set(ll p, T x){
		assert(0 <= p && p < _n);
		p += size;
		for(ll i = log; i >= 1; i--) push(p >> i);
		d[p] = x;
		for(ll i = 1; i <= log; i++) update(p >> i);
	}

	T get(ll p) {
		assert(0 <= p && p < _n);
		p += size;
		for(ll i = log; i >= 1; i--) push(p >> i);
		return d[p];
	}


	T prod(ll l, ll r) {
		assert(0 <= l && l <= r && r <= _n);
		if(l == r) return e();

		l += size;
		r += size;

		for(ll i = log; i >= 1; i--){
			if(((l >> i) << i) != l) push(l >> i);
			if(((r >> i) << i) != r) push((r-1) >> i);
		}
		
		T sml = e(), smr = e();
		while(l < r){
			if(l&1) sml = op(sml, d[l++]);
			if(r&1) smr = op(d[--r], smr);
			l >>= 1;
			r >>= 1;
		}

		return op(sml, smr);
	}

	T all_prod() {return d[1]; }

	void apply(ll p, F f){
		assert(0 <= p && p < _n);
		p += size;
		for(ll i = log; i >= 1; i--) push(p >> i); 
		d[p] = mapping(f, d[p]);
		for(ll i = 1; i <= log; i++) update(p >> i);
	}

	void apply(ll l, ll r, F f){
		assert(0 <= l && l <= r && r <= _n);
		if(l == r) return;

		l += size;
		r += size;

		for(ll i = log; i >= 1; i--){
			if(((l >> i) << i) != l) push(l >> i);
			if(((r >> i) << i) != r) push((r-1) >> i);
		}

		{
			ll l2 = l, r2 = r;
			while(l < r){
				if(l&1) all_apply(l++, f);
				if(r&1) all_apply(--r, f);
				l >>= 1;
				r >>= 1;
			}
			l = l2;
			r = r2;
		}

		for(ll i = 1; i <= log; i++){
			if(((l >> i) << i) != l) update(l >> i);
			if(((r >> i) << i) != r) update((r-1) >> i);
		}
	}

	// f(op(a[l], a[l + 1], ..., a[r - 1])) = trueとなる最大のｒ
	template <bool (*g)(T)> ll max_right(ll l) {
		return max_right(l, [](T x) { return g(x); });
	}
	template <class G> ll max_right(ll l, G g) {
		assert(0 <= l && l <= _n);
		assert(g(e()));
		if (l == _n) return _n;
		l += size;
		for (ll i = log; i >= 1; i--) push(l >> i);
		T sm = e();
		do {
			while (l % 2 == 0) l >>= 1;
			if (!g(op(sm, d[l]))) {
				while (l < size) {
					push(l);
					l = (2 * l);
					if (g(op(sm, d[l]))) {
						sm = op(sm, d[l]);
						l++;
					}
				}
				return l - size;
			}
			sm = op(sm, d[l]);
			l++;
		} while ((l & -l) != l);
		return _n;
	}

	template <bool (*g)(T)> ll min_left(ll r) {
		return min_left(r, [](T x) { return g(x); });
	}
	template <class G> ll min_left(ll r, G g) {
		assert(0 <= r && r <= _n);
		assert(g(e()));
		if (r == 0) return 0;
		r += size;
		for (ll i = log; i >= 1; i--) push((r - 1) >> i);
		T sm = e();
		do {
			r--;
			while (r > 1 && (r % 2)) r >>= 1;
			if (!g(op(d[r], sm))) {
				while (r < size) {
					push(r);
					r = (2 * r + 1);
					if (g(op(d[r], sm))) {
						sm = op(d[r], sm);
						r--;
					}
				}
				return r + 1 - size;
			}
			sm = op(d[r], sm);
		} while ((r & -r) != r);
		return 0;
	}
};

//区間変更・区間最小値取得
using S = double;
using F = double;
const S INF = 8e18;
const F ID = 8e18;

S op(S a, S b){ return std::min(a, b); }
S e(){ return INF; }
S mapping(F f, S x){ return (f == ID ? x : min(x,f)); }
F composition(F f, F g){ return (f == ID ? g : min(f,g)); }
F id(){ return ID; }
// ll n;
// vector<S> v(n);
// LazySegmentTree<S, op, e, F, mapping, composition, id> seg(v);

int main() {
	cout<<fixed<<setprecision(15);
	ll n,k;cin>>n>>k;
	ll sx,sy;cin>>sx>>sy;
	vector<ll> x(n),y(n);
	rep(i,0,n){
		cin>>x[i]>>y[i];
		x[i] -= sx;
		y[i] -= sy;
	}
	vector<S> v(n,INF);
	LazySegmentTree<S, op, e, F, mapping, composition, id> seg(v);
	seg.apply(0,k,0);
	double dist=sqrt(x[0]*x[0]+y[0]*y[0])+sqrt(x[n-1]*x[n-1]+y[n-1]*y[n-1]);
	rep(i,0,n-1){
		double d1=sqrt(x[i]*x[i]+y[i]*y[i])+sqrt(x[i+1]*x[i+1]+y[i+1]*y[i+1]);
		double d2=sqrt((x[i]-x[i+1])*(x[i]-x[i+1])+(y[i]-y[i+1])*(y[i]-y[i+1]));
		dist += d2;
		seg.apply(i+1,min(i+k+1,n),seg.get(i)+d1-d2);
	}
	cout<<dist+seg.get(n-1)<<endl;
	return 0;
}