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

int Z_algorithm(string S) {
	int c = 0, n = S.size();
	vector<int> Z(n, 0);
    ll res = 0;
	for (int i = 1; i < n; i++) {
		int l = i - c;
		if (i + Z[l] < c + Z[c]) {
			Z[i] = Z[l];
		}
		else {
			int j = max(0, c + Z[c] - i);
			while (i + j < n && S[j] == S[i + j])j++;
			Z[i] = j;
			c = i;
		}
        chmax(res,Z[i]);
	}
	Z[0] = n;
	return res;
}

int Z_algorithm2(string S) {
	int c = 0, n = S.size();
	vector<int> Z(n, 0);
    ll res = 0;
	for (int i = 1; i < n; i++) {
		int l = i - c;
		if (i + Z[l] < c + Z[c]) {
			Z[i] = Z[l];
		}
		else {
			int j = max(0, c + Z[c] - i);
			while (i + j < n && S[j] == S[i + j])j++;
			Z[i] = j;
			c = i;
		}
        if(Z[i]+i==n)chmax(res,Z[i]);
	}
	Z[0] = n;
	return res;
}

int main() {
    ll n;cin>>n;
    vector<string> svec(n);
    rep(i,0,n)cin>>svec[i];
    sort(svec.begin(),svec.end(),[](const auto s1, const auto s2){
        return s1.size()>s2.size();
    });
    vector<ll> use(n,1);
    rep(i,0,n){
        string s=svec[i];
        rep(j,0,i){
            string ss= svec[j];
            string x;
            x=s+'&'+ss;
            if(Z_algorithm(x)>=s.size()) use[i]=0;
        }
    }
    vector<string> S;
    rep(i,0,n)if(use[i])S.push_back(svec[i]);
    n=S.size();
    vector<vector<ll>> prefix(n,vector<ll>(n,0));
    rep(i,0,n)rep(j,0,n){
        if(i==j)continue;
        prefix[i][j]=Z_algorithm2(S[j]+'&'+S[i]);
    }
    vector<vector<ll>> dp(1<<n,vector<ll>(n,INF));
    rep(i,0,n)dp[1<<i][i]=S[i].size();
    rep(i,1,1<<n)rep(j,0,n)rep(k,0,n){
        if(!(i>>k&1))chmin(dp[i+(1<<k)][k],dp[i][j]+S[k].size()-prefix[j][k]);
    }
    ll ans=INF;
    rep(i,0,n)chmin(ans,dp[(1<<n)-1][i]);
    cout<<ans<<endl;
    // rep(i,0,n){
    //     rep(j,0,n)cout<<prefix[i][j]<<" ";
    //     cout<<endl;
    // }
    return 0;
}