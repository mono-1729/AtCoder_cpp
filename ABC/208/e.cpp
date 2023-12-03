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

int main() {
	string n;ll k;cin>>n>>k;
	vector<map<ll,ll>> dp(18),dp2(18);
	rep(i,0,10) dp[0][i] = 1;
	rep(i,1,18)for(auto p:dp[i-1])rep(j,0,10) dp[i][p.first*j] += p.second;
	rep(i,1,10) dp2[0][i] = 1;
	rep(i,1,18){
		dp2[i] = dp2[i-1];
		for(auto p:dp[i-1])rep(j,1,10) dp2[i][p.first*j] += p.second;
	}
	vector<vector<ll>> sum1(18,{0LL}),sum2(18,{0LL});
	vector<vector<pll>> nums1(18),nums2(18);
	rep(i,0,18){
		for(auto p:dp[i]){
			nums1[i].push_back(p);
			sum1[i].push_back(sum1[i].back()+p.second);
		}
		for(auto p:dp2[i]){
			nums2[i].push_back(p);
			sum2[i].push_back(sum2[i].back()+p.second);
		}
	}
	ll ans = 0;
	ll prod = 1;
	rep(i,0,n.size()){
		ll x = n[i]-'0';
		if(i==n.size()-1){
			rep(j,0,x+1) if(prod*j<=k) ans++;
		}
		else{
			ll ind;
			rep(j,0,x){
				if(prod*j==0) {
					if(i==0 &&j==0) {
						ind = lower_bound(nums2[n.size()-i-2].begin(), nums2[n.size()-i-2].end(), pll(k+1,0LL))-nums2[n.size()-i-2].begin();
						ans += sum2[n.size()-i-2][ind];
					}
					else ans+=sum1[n.size()-i-2].back();
				}
				else{
					ind = lower_bound(nums1[n.size()-i-2].begin(), nums1[n.size()-i-2].end(), pll(k/(prod*j)+1,0LL))-nums1[n.size()-i-2].begin();
					ans += sum1[n.size()-i-2][ind];
				}
			}
			prod *= x;
		}
	}
	if(n.size()==1) ans--;
	cout<<ans<<endl;
	return 0;
}