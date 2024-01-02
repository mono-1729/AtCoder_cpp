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

class UnionFind {
	vector<ll> parent, maxi, mini;
public:
	UnionFind(ll n_ = 1): parent(n_, -1), maxi(n_), mini(n_){
		iota(maxi.begin(), maxi.end(), 0);
		iota(mini.begin(), mini.end(), 0);
	}

	inline ll root(ll n){
		return (parent[n] < 0? n:parent[n] = root(parent[n]));
	}

	inline bool same(ll x, ll y){
		return root(x) == root(y);
	}

	inline void unite(ll x, ll y){
		ll rx = root(x);
		ll ry = root(y);
		if(rx == ry) return;
		if(parent[rx] > parent[ry]) swap(rx, ry);
		parent[rx] += parent[ry];
		parent[ry] = rx;
		maxi[x] = std::max(maxi[x],maxi[y]);
		mini[x] = std::min(mini[x],mini[y]);
	}

	inline ll min(ll x){
		return mini[root(x)];
	}

	inline ll max(ll x){
		return mini[root(x)];
	}

	inline ll size(ll x){
		return (-parent[root(x)]);
	}

	inline ll operator[](ll x){
		return root(x);
	}

	inline void print(){
		rep(i, 0, (ll)parent.size()) cout << root(i) << " ";
		cout << endl;
	}

	void clear(){
		rep(i, 0, (ll)parent.size()){
			parent[i] = -1;
		}
		iota(maxi.begin(), maxi.end(), 0);
		iota(mini.begin(), mini.end(), 0);
	}
};

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
	void add(ll i, X x) {
		i += n - 1;
		dat[i].num += x;
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
using S = struct{
	ll num;
	ll pos;
};

auto fx = [](S x1, S x2) -> S{ 
	if(x1.num<=x2.num) return x1;
	else return x2;
};
auto fx2 = [](S x1, S x2) -> S{ 
	if(x1.num<=x2.num) return x2;
	else return x1;
 };
S ex = {INF,INF};
S ex2 = {-1,-1};

int main() {
	ll n,m;cin>>n>>m;
	vector<vector<ll>> g(n);
	vector<ll> d(n);
	rep(i,0,n) cin>>d[i];
	ll sum=0;
	rep(i,0,n) sum+=d[i];
	if(sum!=2*(n-1)){
		cout<<-1<<endl;
		return 0;
	}
	UnionFind uf(n);
	rep(i,0,m){
		ll a,b;cin>>a>>b;
		a--;b--;
		if(!uf.same(a,b)){
			uf.unite(a,b);
			g[a].push_back(b);
			g[b].push_back(a);
		}
		else{
			cout<<-1<<endl;
			return 0;
		}
	}
	vector<vector<ll>> ver(n);
	rep(i,0,n){
		if(d[i]<g[i].size()){
			cout<<-1<<endl;
			return 0;
		}
		rep(j,0,d[i]-g[i].size()) ver[uf.root(i)].push_back(i);
	}
	SegTree<S> segmin(n,fx,ex),segmax(n,fx2,ex2);
	rep(i,0,n){
		if(uf.root(i)==i){
			if(ver[i].size()==0){
				cout<<-1<<endl;
				return 0;
			}
			segmin.set(i,{(ll)ver[i].size(),i});
			segmax.set(i,{(ll)ver[i].size(),i});
		}
		else{
			segmin.set(i,{INF,INF});
			segmax.set(i,{-1,-1});
		}
	} 
	segmin.build();
	segmax.build();
	rep(i,0,n-m-1){
		auto p1=segmin.query(0,n);
		auto p2=segmax.query(0,n);
		//cout<<p1.num<<" "<<p1.pos<<" "<<p2.num<<" "<<p2.pos<<endl;
		cout<<ver[p1.pos].back()+1<<" "<<ver[p2.pos].back()+1<<endl;
		ver[p1.pos].pop_back();
		ver[p2.pos].pop_back();
		if(p1.num==1)segmin.update(p1.pos,{INF,INF});
		else segmin.update(p1.pos,{p1.num-1,p1.pos});
		if(p2.num==1)segmin.update(p2.pos,{INF,INF});
		else segmin.update(p2.pos,{p2.num-1,p2.pos});
		segmax.update(p1.pos,{p1.num-1,p1.pos});
		segmax.update(p2.pos,{p2.num-1,p2.pos});
	}
	return 0;
}