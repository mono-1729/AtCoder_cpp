#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
//constexpr ll MOD = 1000000007;
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
mint dp[70][10][10][10][2][2][2];

int main() {
	ll n_,a1,a2,a3;cin>>n_>>a1>>a2>>a3;
	bitset<60> bs(n_);
	vector<int> n;
	rep(i,0,60) n.push_back(bs[i]);
	reverse(n.begin(),n.end());
	dp[0][0][0][0][0][0][0] = 1;
	rep(i,0,n.size()){
		rep(j,0,a1){
			rep(k,0,a2){
				rep(l,0,a3){
					if(n[i]){
						rep(m,0,2)rep(o,0,2)rep(p,0,2){
							dp[i+1][j*2%a1][k*2%a2][l*2%a3][1][1][1]+=dp[i][j][k][l][m][o][p];
							dp[i+1][(j*2+1)%a1][(k*2+1)%a2][l*2%a3][m][o][1]+=dp[i][j][k][l][m][o][p];
							dp[i+1][(j*2+1)%a1][k*2%a2][(l*2+1)%a3][m][1][p]+=dp[i][j][k][l][m][o][p];
							dp[i+1][j*2%a1][(k*2+1)%a2][(l*2+1)%a3][1][o][p]+=dp[i][j][k][l][m][o][p];
						}
					}else{
						rep(m,0,2)rep(o,0,2)rep(p,0,2){
							dp[i+1][j*2%a1][k*2%a2][l*2%a3][m][o][p]+=dp[i][j][k][l][m][o][p];
							if(m==1 && o==1)dp[i+1][(j*2+1)%a1][(k*2+1)%a2][l*2%a3][m][o][p]+=dp[i][j][k][l][m][o][p];
							if(m==1 && p==1)dp[i+1][(j*2+1)%a1][k*2%a2][(l*2+1)%a3][m][o][p]+=dp[i][j][k][l][m][o][p];
							if(o==1 && p==1)dp[i+1][j*2%a1][(k*2+1)%a2][(l*2+1)%a3][m][o][p]+=dp[i][j][k][l][m][o][p];
						}
					}
				}
			}
		}
	}
	mint ans=0;
	rep(i,0,2)rep(j,0,2)rep(k,0,2){
		ans+=dp[n.size()][0][0][0][i][j][k];
	}
	ans-=1;
	ans-=n_/lcm(a1,a2);
	ans-=n_/lcm(a1,a3);
	ans-=n_/lcm(a2,a3);
	cout<<ans<<endl;
	return 0;
}