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
    ll n,d;cin>>n>>d;
    vector<vector<ll>> a(n,vector<ll>(n));
    rep(i,0,n)rep(j,0,n) cin>>a[i][j];
    vector<vector<ll>> b(n,vector<ll>(n));
    rep(i,0,n)rep(j,0,n) b[i][j]=a[i][j];
    ll cost1 = 0,cost2 = 0;
    rep(i,0,n)rep(j,0,n){
        if((i+j)%2==0){
            vector<pll> vec,vec2;
            if(i>0) vec.push_back({a[i-1][j]-d+1,a[i-1][j]+d-1});
            if(j>0) vec.push_back({a[i][j-1]-d+1,a[i][j-1]+d-1});
            if(i<n-1) vec.push_back({a[i+1][j]-d+1,a[i+1][j]+d-1});
            if(j<n-1) vec.push_back({a[i][j+1]-d+1,a[i][j+1]+d-1});
            sort(vec.begin(),vec.end());
            for(auto x:vec){
                if(vec2.empty()||vec2.back().second+1<x.first){
                    vec2.push_back(x);
                }
                else{
                    vec2.back().second = x.second;
                }
            }
            ll min_cost = 1e18,num = 0;
            for(auto x:vec2){
                if(min_cost>abs(x.first-1-a[i][j])){
                    min_cost = abs(x.first-1-a[i][j]);
                    num = x.first-1;
                }
                if(min_cost>abs(x.second+1-a[i][j])){
                    min_cost = abs(x.second+1-a[i][j]);
                    num = x.second+1;
                }
            }
            cost1 += min_cost;
            a[i][j] = num;
        }
        if((i+j)%2==1){
            vector<pll> vec,vec2;
            if(i>0) vec.push_back({b[i-1][j]-d+1,b[i-1][j]+d-1});
            if(j>0) vec.push_back({b[i][j-1]-d+1,b[i][j-1]+d-1});
            if(i<n-1) vec.push_back({b[i+1][j]-d+1,b[i+1][j]+d-1});
            if(j<n-1) vec.push_back({b[i][j+1]-d+1,b[i][j+1]+d-1});
            sort(vec.begin(),vec.end());
            for(auto x:vec){
                if(vec2.empty()||vec2.back().second+1<x.first){
                    vec2.push_back(x);
                }
                else{
                    vec2.back().second = x.second;
                }
            }
            ll min_cost = 1e18,num=0;
            for(auto x:vec2){
                if(min_cost>abs(x.first-1-b[i][j])){
                    min_cost = abs(x.first-1-b[i][j]);
                    num = x.first-1;
                }
                if(min_cost>abs(x.second+1-b[i][j])){
                    min_cost = abs(x.second+1-b[i][j]);
                    num = x.second+1;
                }
            }
            cost2 += min_cost;
            b[i][j] = num;
        }
    }
    if(cost1>cost2){
        rep(i,0,n){
            rep(j,0,n){
                cout<<b[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    else{
        rep(i,0,n){
            rep(j,0,n){
                cout<<a[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    //cout<<cost1<<" "<<cost2<<endl;
    return 0;
}