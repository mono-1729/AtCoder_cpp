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

void recursive_comb(int *indexes, int s, int rest, std::function<void(int *)> f) {
  if (rest == 0) {
    f(indexes);
  } else {
    if (s < 0) return;
    recursive_comb(indexes, s - 1, rest, f);
    indexes[rest - 1] = s;
    recursive_comb(indexes, s - 1, rest - 1, f);
  }
}
class UnionFind {
	vector<ll> parent, maxi, mini;
	inline ll root(ll n){
		return (parent[n] < 0? n:parent[n] = root(parent[n]));
	}
public:
	UnionFind(ll n_ = 1): parent(n_, -1), maxi(n_), mini(n_){
		iota(maxi.begin(), maxi.end(), 0);
		iota(mini.begin(), mini.end(), 0);
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

template<typename T>
vector<vector<T>> combination(vector<T> &elems, int r) {
    vector<vector<T>> v{};
    vector<T> v1(r);
    int n = elems.size();
    function<void(int,int,int)> _dfs = [&](int bit,int now,int num_decided){
        if (num_decided == r) {
            int index = 0;
            for(int i=0; i<n;i++){
                if(bit&(1<<i)){
                    v1[index] = elems[i];
                    index++;
                }
            }
            v.push_back(v1);
            return;
        }
        if(now == n)return;
        _dfs(bit+(1<<now),now+1,num_decided+1);
        _dfs(bit,now+1,num_decided);
    };
    _dfs(0,0,0);
    return v;
}

int main() {
	ll n,m,k;cin>>n>>m>>k;
	vector<ll> u(m),v(m),w(m);
	rep(i,0,m){
		cin>>u[i]>>v[i]>>w[i];
		u[i]--;v[i]--;
	}
	vector<ll>indexes(m);
	rep(i,0,m)indexes[i]=i;
	ll ans=k;
	vector<vector<ll>> comb=combination(indexes,n-1);
	for(auto i:comb){
		ll tmp=0;
		UnionFind uf(n);
		for(auto j:i){
			tmp+=w[j];
			uf.unite(u[j],v[j]);
			tmp%=k;
		}
		if(uf.size(0)==n)chmin(ans,tmp);
	}
	cout<<ans<<endl;
	return 0;
}