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

int main() {
	ll v1,v2,v3;cin>>v1>>v2>>v3;
	ll a1,b1,c1,a2,b2,c2,a3,b3,c3;
	a1=0;a2=0;a3=0;
	if(v1==1029){
        if(v2==0 && v3==0){
            cout<<"Yes"<<endl;
            cout<<0<<" "<<10<<" "<<20<<" "<<30<<" "<<40<<" "<<50<<" "<<60<<" "<<70<<" "<<80<<endl;
        }else cout<<"No"<<endl;
        return 0;
	}
	rep(i,-7,8)rep(j,-7,8)rep(k,-7,8){
		b1=i;b2=j;b3=k;
		rep(l,min(0LL,i)-7,max(0LL,i)+8)rep(m,min(0LL,j)-7,max(0LL,j)+8)rep(n,min(0LL,k)-7,max(0LL,k)+8){
			c1=l;c2=m;c3=n;
			ll num1=0,num2=0,num3=0;
			num3 = max(7-max(max(a1,b1),c1)+min(min(a1,b1),c1),0LL)*max(7-max(max(a2,b2),c2)+min(min(a2,b2),c2),0LL)*max(7-max(max(a3,b3),c3)+min(min(a3,b3),c3),0LL);
			if(num3!=v3)continue;
			num2 += max(7-max(a1,b1)+min(a1,b1),0LL)*max(7-max(a2,b2)+min(a2,b2),0LL)*max(7-max(a3,b3)+min(a3,b3),0LL);
			num2 += max(7-max(a1,c1)+min(a1,c1),0LL)*max(7-max(a2,c2)+min(a2,c2),0LL)*max(7-max(a3,c3)+min(a3,c3),0LL);
			num2 += max(7-max(b1,c1)+min(b1,c1),0LL)*max(7-max(b2,c2)+min(b2,c2),0LL)*max(7-max(b3,c3)+min(b3,c3),0LL);
			num2 -= num3*3;
			if(num2!=v2)continue;
            if(v1!=1029-num2*2-num3*3) continue;
			cout<<"Yes"<<endl;
			cout<<a1<<" "<<a2<<" "<<a3<<" "<<b1<<" "<<b2<<" "<<b3<<" "<<c1<<" "<<c2<<" "<<c3<<endl;
            return 0;
		}
	}
	cout<<"No"<<endl;
	return 0;
}