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

int main() {
	ll n,a,b,c;cin>>n>>a>>b>>c;
	vector<ll> l(n);
	vector<vector<pll>>num(7);
	ll ans=1LL<<62;
	rep(i,0,n) {
		cin>>l[i];
		num[0].push_back({((l[i]-1)/a+1)*a-l[i],i});
		num[1].push_back({((l[i]-1)/b+1)*b-l[i],i});
		num[2].push_back({((l[i]-1)/c+1)*c-l[i],i});
		num[3].push_back({((l[i]-1)/(lcm(a,b))+1)*lcm(a,b)-l[i],i});
		num[4].push_back({((l[i]-1)/(lcm(a,c))+1)*lcm(a,c)-l[i],i});
		num[5].push_back({((l[i]-1)/lcm(b,c)+1)*lcm(b,c)-l[i],i});
		num[6].push_back({((l[i]-1)/(lcm(lcm(a,b),c))+1)*lcm(lcm(a,b),c)-l[i],i});
	}
	rep(i,0,7) sort(num[i].begin(),num[i].end());
	chmin(ans,num[6][0].first);
	if(n==1){
		cout<<ans<<endl;
		return 0;
	}
	if(num[5][0].second==num[0][0].second){
		chmin(ans,num[5][0].first+num[0][1].first);
		chmin(ans,num[5][1].first+num[0][0].first);
	} 
	else chmin(ans,num[5][0].first+num[0][0].first);
	if(num[4][0].second==num[1][0].second){
		chmin(ans,num[4][0].first+num[1][1].first);
		chmin(ans,num[4][1].first+num[1][0].first);
	} 
	else chmin(ans,num[4][0].first+num[1][0].first);
	if(num[3][0].second==num[2][0].second){
		chmin(ans,num[3][0].first+num[2][1].first);
		chmin(ans,num[3][1].first+num[2][0].first);
	} 
	else chmin(ans,num[3][0].first+num[2][0].first);
	//cout<<num[3][0].first<<" "<<num[2][0].first<<"a"<<num[3][0].second<<" "<<num[2][0].second<<"a"<<endl;
	if(n==2){
		cout<<ans<<endl;
		return 0;
	}
	vector<ll> v={0,1,2};
	do{
		set<ll> s;
		ll x=0;
		x+=num[v[0]][0].first;
		s.insert(num[v[0]][0].second);
		if(s.find(num[v[1]][0].second)!=s.end()){
			x+=num[v[1]][1].first;
			s.insert(num[v[1]][1].second);
		}
		else{
			x+=num[v[1]][0].first;
			s.insert(num[v[1]][0].second);
		}
		if(s.find(num[v[2]][0].second)!=s.end()){
			if(s.find(num[v[2]][1].second)!=s.end()) x+=num[v[2]][2].first;
			else x+=num[v[2]][1].first;
		}
		else{
			x+=num[v[2]][0].first;
		}
		chmin(ans,x);

	}while(next_permutation(v.begin(),v.end()));
	cout<<ans<<endl;
	return 0;
}