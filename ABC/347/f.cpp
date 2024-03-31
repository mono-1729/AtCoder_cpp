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
    ll n,m;cin>>n>>m;
    vector<vector<ll>> a(n, vector<ll>(n));
    rep(i,0,n)rep(j,0,n)cin>>a[i][j]; 
    vector<vector<ll>> sum(n+1, vector<ll>(n+1));
    rep(i,0,n)rep(j,0,n)sum[i+1][j+1] = a[i][j];
    rep(i,0,n)rep(j,0,n+1)sum[i+1][j] += sum[i][j];
    rep(i,0,n+1)rep(j,0,n)sum[i][j+1] += sum[i][j];
    auto calc = [&](ll x1, ll y1){
        return sum[x1][y1] - sum[x1][y1-m] - sum[x1-m][y1] + sum[x1-m][y1-m];
    };
    vector<vector<ll>> ul(n, vector<ll>(n)), ur(n, vector<ll>(n)), dl(n, vector<ll>(n)), dr(n, vector<ll>(n));
    rep(i,0,n)rep(j,0,n){
        if(i>=m-1 &&j>=m-1) ul[i][j] = calc(i+1, j+1);
        if(i>=m-1 &&j+m<=n) ur[i][j] = calc(i+1, j+m);
        if(i+m<=n &&j>=m-1) dl[i][j] = calc(i+m, j+1);
        if(i+m<=n &&j+m<=n) dr[i][j] = calc(i+m, j+m);
    }
    rep(i,0,n-1)rep(j,0,n)chmax(ul[i+1][j],ul[i][j]);
    rep(i,0,n)rep(j,0,n-1)chmax(ul[i][j+1],ul[i][j]);
    rep(i,0,n-1)rep(j,0,n)chmax(ur[i+1][j],ur[i][j]);
    rep(i,0,n)rrep(j,n-1,1)chmax(ur[i][j-1],ur[i][j]);
    rrep(i,n-1,1)rep(j,0,n)chmax(dl[i-1][j],dl[i][j]);
    rep(i,0,n)rep(j,0,n-1)chmax(dl[i][j+1],dl[i][j]);
    rrep(i,n-1,1)rep(j,0,n)chmax(dr[i-1][j],dr[i][j]);
    rep(i,0,n)rrep(j,n-1,1)chmax(dr[i][j-1],dr[i][j]);
    ll ans = 0;
    rep(i,m-1,n)rep(j,m-1,n){
        ll num = calc(i+1,j+1);
        if(i-m>=m-1 && i+m<n)chmax(ans,num+ul[i-m][n-1]+dl[i+1][n-1]);
        if(j-m>=m-1 && j+m<n)chmax(ans,num+ul[n-1][j-m]+ur[n-1][j+1]);
        if(i-m>=m-1 && j+m<n)chmax(ans,num+ul[i-m][n-1]+dr[i-m+1][j+1]);
        if(i+m<n && j-m>=m-1)chmax(ans,num+ul[n-1][j-m]+dr[i+1][j-m+1]);
        if(i+m<n && j+m<n)chmax(ans,num+ur[n-1][j+1]+dl[i+1][j]);
        if(i+m<n && j+m<n)chmax(ans,num+ur[i][j+1]+dl[i+1][n-1]);
    }
    cout<<ans<<endl;
    return 0;
}