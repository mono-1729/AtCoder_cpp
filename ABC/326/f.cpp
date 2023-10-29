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
	ll n,x,y;cin>>n>>x>>y;
	vector<ll> xdist1,xdist2, ydist1,ydist2;
	rep(i,0,n){
		ll tmp;cin>>tmp;
		if(i<40){
			if(i%2==0) ydist1.push_back(tmp);
			else xdist1.push_back(tmp);
		}
		else{
			if(i%2==0) ydist2.push_back(tmp);
			else xdist2.push_back(tmp);
		}
	}
	vector<ll> xlist, ylist;
	map<ll,ll> xmap, ymap;
	rep(i,0,1<<xdist1.size()){
		ll tmp = 0;
		rep(j,0,xdist1.size()){
			if(i>>j&1) tmp += xdist1[j];
			else tmp -= xdist1[j];
		}
		xmap[tmp]=i;
	}
	rep(i,0,1<<ydist1.size()){
		ll tmp = 0;
		rep(j,0,ydist1.size()){
			if(i>>j&1) tmp += ydist1[j];
			else tmp -= ydist1[j];
		}
		ymap[tmp]=i;
	}
	vector<ll> xans, yans;
	bool xflag = false,yflag = false;
	if(xdist2.size()==0){
		if(xmap.count(x)){
			rep(i,0,xdist1.size()){
				if(xmap[x]>>i&1) xans.push_back(1);
				else xans.push_back(0);
			}
			xflag = true;
		}
	}
	else{
		rep(i,0,1<<xdist2.size()){
			ll tmp = 0;
			rep(j,0,xdist2.size()){
				if(i>>j&1) tmp += xdist2[j];
				else tmp -= xdist2[j];
			}
			if(xmap.count(x-tmp)){
				rep(j,0,xdist1.size()){
					if(xmap[x-tmp]>>j&1) xans.push_back(1);
					else xans.push_back(0);
				}
				rep(j,0,xdist2.size()){
					if(i>>j&1) xans.push_back(1);
					else xans.push_back(0);
				}
				xflag = true;
				break;
			}
		}
	}
	if(ydist2.size()==0){
		if(ymap.count(y)){
			rep(i,0,ydist1.size()){
				if(ymap[y]>>i&1) yans.push_back(1);
				else yans.push_back(0);
			}
			yflag = true;
		}
	}
	else{
		rep(i,0,1<<ydist2.size()){
			ll tmp = 0;
			rep(j,0,ydist2.size()){
				if(i>>j&1) tmp +=ydist2[j];
				else tmp -= ydist2[j];
			}
			if(ymap.count(y-tmp)){
				rep(j,0,ydist1.size()){
					if(ymap[y-tmp]>>j&1) yans.push_back(1);
					else yans.push_back(0);
				}
				rep(j,0,ydist2.size()){
					if(i>>j&1) yans.push_back(1);
					else yans.push_back(0);
				}
				yflag = true;
				break;
			}
		}
	}
	if(xflag &&yflag){
		cout<<"Yes"<<endl;
		ll now=1;
		rep(i,0,n){
			if(i%2==0){
				if(yans[i/2]==1){
					if(now==1)cout<<'L';
					else cout<<'R';
					now=0;
				}
				else{
					if(now==1)cout<<'R';
					else cout<<'L';
					now=2;
				}
			}
			else{
				if(xans[i/2]==1){
					if(now==0)cout<<'R';
					else cout<<'L';
					now=1;
				}
				else{
					if(now==0)cout<<'L';
					else cout<<'R';
					now=3;
				}
			}
		}
		cout<<endl;
		return 0;
	}
	else{
		cout<<"No"<<endl;
		return 0;
	}
	return 0;
}