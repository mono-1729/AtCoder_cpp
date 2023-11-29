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
	ll n,k;cin>>n>>k;
	map<ll,ll>xmp,ymp;
	rep(i,0,n){
		ll x,y;cin>>x>>y;
		xmp[x]++;
		ymp[y]++;
	}
	vector<pll> xcost,ycost;
	auto xmi=xmp.begin(),xma=prev(xmp.end());
	auto ymi=ymp.begin(),yma=prev(ymp.end());
	while(xmi!=xma){
		if((*xmi).second<(*xma).second){
			ll c=(*xmi).second;
			xcost.push_back({xma->first-xmi->first,xmi->second});
			(*xmi).second-=c;
			xmi++;
			(*xmi).second+=c;
		}
		else{
			ll c=(*xma).second;
			xcost.push_back({xma->first-xmi->first,xma->second});
			(*xma).second-=c;
			xma--;
			(*xma).second+=c;
		}
	}
	xcost.push_back({0,1e18});
	while(ymi!=yma){
		if((*ymi).second<(*yma).second){
			ll c=(*ymi).second;
			ycost.push_back({yma->first-ymi->first,ymi->second});
			(*ymi).second-=c;
			ymi++;
			(*ymi).second+=c;
		}
		else{
			ll c=(*yma).second;
			ycost.push_back({yma->first-ymi->first,yma->second});
			(*yma).second-=c;
			yma--;
			(*yma).second+=c;
		}
	}
	ycost.push_back({0,1e18});
	ll l=-1,r=1e9;
	while(r-l>1){
		ll m=(l+r)/2;
		ll cnt=0;
		ll index=0;
		if(m<xcost[0].first)while(true){
			if(xcost[index+1].first<=m){
				cnt+=xcost[index].second*(xcost[index].first-m);
				break;
			}
			else cnt+=xcost[index].second*(xcost[index].first-xcost[index+1].first);
			index++;
		}
		index=0;
		if(m<ycost[0].first)while(true){
			if(ycost[index+1].first<=m){
				cnt+=ycost[index].second*(ycost[index].first-m);
				break;
			}
			else cnt+=ycost[index].second*(ycost[index].first-ycost[index+1].first);
			index++;
		}
		if(cnt<=k)r=m;
		else l=m;
	}
	cout<<r<<endl;
	return 0;
}