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

ll h,w,k;
vector<vector<char>> sx(801,vector<char>(801));

// sを始点とする各頂点への距離の最小値を格納した配列を返す
vector<vector<tuple<ll,ll,ll>>>  dijk(ll s){
	priority_queue<tuple<ll,ll,ll,ll>, vector<tuple<ll,ll,ll,ll>>, greater<tuple<ll,ll,ll,ll>>> que;
	vector<vector<tuple<ll,ll,ll>>> dist(h,vector<tuple<ll,ll,ll>>(w,{INF,INF,INF}));
	que.push({1,0,0,s});
	dist[s/w][s%w] = {1,0,0};
	while(!que.empty()){
		tuple<ll,ll,ll,ll> q = que.top(); que.pop();
		ll d0 = get<0>(q), d1 = get<1>(q),d2 = get<2>(q),u = get<3>(q);
		if(dist[u/w][u%w] < make_tuple(d0,d1,d2)) continue;
		vector<pll> tmp={{u/w-1,u%w},{u/w+1,u%w},{u/w,u%w-1},{u/w,u%w+1}};
		for(auto nq:tmp){
			if(nq.first<0||nq.first>=h||nq.second<0||nq.second>=w) continue;
			ll nd0,nd1,nd2;
			if(sx[nq.first][nq.second]=='#') {
				if(d2+1>k*(d0-1)|| d1+1>k){
					nd0=d0+1;
					nd1=1;
					nd2=d2+1;
				}
				else{
					nd0=d0;
					nd1=d1+1;
					nd2=d2+1;
				}
			}
			else {
				if(d1+1>k){
					nd0=d0+1;
					nd1=1;
					nd2=d2;
				}
				else {
					nd0=d0;
					nd1=d1+1;
					nd2=d2;
				}
			}
			//cout<<nq.first<<","<<nq.second<<":"<<nd.first<<","<<nd.second<<endl;
			if(dist[nq.first][nq.second] > make_tuple(nd0,nd1,nd2)){
				dist[nq.first][nq.second] = {nd0,nd1,nd2};
				que.push({nd0,nd1,nd2,nq.first*w+nq.second});
			}
		}
	}
	return dist;
}

int main() {
	cin>>h>>w>>k;
	ll si,sj;
	rep(i,0,h)rep(j,0,w){
		cin>>sx[i][j];
		if(sx[i][j]=='S'){
			si=i;
			sj=j;
		}
	}
	vector<vector<tuple<ll,ll,ll>>>  dist=dijk(si*w+sj);
	ll ans=INF;
	rep(i,0,h)rep(j,0,w){
		if(i==0||j==0||i==h-1||j==w-1) chmin(ans,get<0>(dist[i][j]));
	}
	cout<<ans<<endl;
	// rep(i,0,h){
	// 	rep(j,0,w){
	// 		cout<<get<0>(dist[i][j])<<","<<get<1>(dist[i][j])<<","<<get<2>(dist[i][j])<<" ";
	// 	}
	// 	cout<<endl;
	// }
	return 0;
}