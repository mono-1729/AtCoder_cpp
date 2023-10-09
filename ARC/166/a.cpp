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
	int t;cin>>t;
	rep(_,0,t){
		ll n;cin>>n;
		bool flag=false;
		string x,y;cin>>x>>y;
		ll anum=0,bnum=0,cnum=0;
		ll anum2=0,bnum2=0,cnum2=0;
		ll pre=0;
		rep(i,0,n){
			if(x[i]=='A')anum++;
			if(x[i]=='B')bnum++;
			if(x[i]=='C')cnum++;
			if(y[i]=='A')anum2++;
			if(y[i]=='B')bnum2++;
			if(y[i]=='C')cnum2++;
			if(bnum>bnum2){
				flag=true;
				break;
			}
			if(y[i]=='C'){
				if(x[i]!='C'){
					flag=true;
					break;
				}
				if(anum>anum2 || bnum>bnum2){
					flag=true;
					break;
				}
				rep(j,pre,i){
					if(x[j]=='C'){
						if(anum<anum2){
							anum++;
							cnum--;
							x[j]='A';
						}
						else if(bnum<bnum2){
							bnum++;
							cnum--;
							x[j]='B';
						}
					}
				}
				anum=0;bnum=0;cnum=0;
				anum2=0;bnum2=0;cnum2=0;
				pre=i+1;
			}
		}
		if(anum>anum2 || bnum>bnum2){
			flag=true;
		}
		rep(j,pre,n){
			if(x[j]=='C'){
				if(anum<anum2){
					anum++;
					cnum--;
					x[j]='A';
				}
				else if(bnum<bnum2){
					bnum++;
					cnum--;
					x[j]='B';
				}
			}
		}
		
		if(flag){
			cout<<"No"<<endl;
		}else{
			anum=0;bnum=0;cnum=0;
			anum2=0;bnum2=0;cnum2=0;
			rep(i,0,n){
				if(x[i]=='A')anum++;
				if(x[i]=='B')bnum++;
				if(x[i]=='C')cnum++;
				if(y[i]=='A')anum2++;
				if(y[i]=='B')bnum2++;
				if(y[i]=='C')cnum2++;
				if(bnum>bnum2){
					flag=true;
					break;
				}
				if(y[i]=='C'){
					if(x[i]!='C'){
						flag=true;
						break;
					}
					if(anum>anum2 || bnum>bnum2){
						flag=true;
						break;
					}
					anum=0;bnum=0;cnum=0;
					anum2=0;bnum2=0;cnum2=0;
				}
			}
			if(anum>anum2 || bnum>bnum2){
				flag=true;
			}
			if(flag){
				cout<<"No"<<endl;
			}else{
				cout<<"Yes"<<endl;
			}
		}

	}
	return 0;
}