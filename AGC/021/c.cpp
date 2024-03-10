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
    cout<<fixed<<setprecision(15);
    ll n;cin>>n;
    vector<double> ans(n,0);
    vector<tuple<ll,ll,ll>>pos;
    map<pll,ll>mp;
    rep(i,0,n){
        ll x,y;cin>>x>>y;
        if(mp[{x,y}]==0)pos.push_back({x,y,i});
        mp[{x,y}]++;
    }
    sort(pos.begin(),pos.end());
    vector<tuple<ll,ll,ll>> up,down;
    rrep(i,n-1,0){
        while(up.size()>=2){
            pll vec1 = {get<0>(pos[i])-get<0>(up[up.size()-1]),get<1>(pos[i])-get<1>(up[up.size()-1])};
            pll vec2 = {get<0>(up[up.size()-2])-get<0>(up[up.size()-1]),get<1>(up[up.size()-2])-get<1>(up[up.size()-1])};
            if((vec1.first*vec2.second-vec1.second*vec2.first)<=0) up.pop_back();
            else break;
        }
        up.push_back(pos[i]);
    }
    rrep(i,n-1,0){
        while(down.size()>=2){
            pll vec1 = {get<0>(pos[i])-get<0>(down[down.size()-1]),get<1>(pos[i])-get<1>(down[down.size()-1])};
            pll vec2 = {get<0>(down[down.size()-2])-get<0>(down[down.size()-1]),get<1>(down[down.size()-2])-get<1>(down[down.size()-1])};
            if((vec1.first*vec2.second-vec1.second*vec2.first)>=0) down.pop_back();
            else break;
        }
        down.push_back(pos[i]);
    }
    rrep(i,down.size()-2,1)up.push_back(down[i]);
    vector<double>deg;
    ll m=up.size();
    rep(i,0,m){
        deg.push_back(atan2(-get<0>(up[(i+1)%m])+get<0>(up[i]),get<1>(up[(i+1)%m])-get<1>(up[i])));
    }
    rep(i,0,m){
        double num = deg[i]-deg[(i+m-1)%m]>=0 ? deg[i]-deg[(i+m-1)%m] : deg[i]-deg[(i+m-1)%m]+2*M_PI;
        ans[get<2>(up[i])]=num/(2*M_PI);
    }
    rep(i,0,n)cout<<ans[i]<<endl;
    return 0;
}