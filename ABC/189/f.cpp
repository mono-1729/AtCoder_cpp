#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;
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

template <typename X>
struct SegTree {
    using FX = function<X(X, X)>; // X•X -> X となる関数の型
    ll n;
    FX fx;
    const X ex;
    vector<X> dat;
    SegTree(ll n_, FX fx_, X ex_) : n(), fx(fx_), ex(ex_), dat(n_ * 4, ex_) {
        ll x = 1;
        while (n_ > x) {
            x *= 2;
        }
        n = x;
    }
    void set(ll i, X x) { dat[i + n - 1] = x; }
    X get(ll i){return dat[i + n - 1];}
    void build() {
        for (ll k = n - 2; k >= 0; k--) dat[k] = fx(dat[2 * k + 1], dat[2 * k + 2]);
    }
    void update(ll i, X x) {
        i += n - 1;
        dat[i] = x;
        while (i > 0) {
            i = (i - 1) / 2;  // parent
            dat[i] = fx(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }
    X query(ll a, ll b) { return query_sub(a, b, 0, 0, n); }
    X query_sub(ll a, ll b, ll k, ll l, ll r) {
        if (r <= a || b <= l) {
            return ex;
        } else if (a <= l && r <= b) {
            return dat[k];
        } else {
            X vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
            X vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
            return fx(vl, vr);
        }
    }
};

using S = struct {
    double prob;
    double exp;
};


auto fx = [](S x1, S x2) -> S{ return {x1.prob+x2.prob,x1.exp+x2.exp};};
S ex = {0,0};

int main() {
    cout<<fixed<<setprecision(15);
    ll n,m,k;cin>>n>>m>>k;
    vector<ll>a(k);
    rep(i,0,k)cin>>a[i];
    ll cnt = 0;
    ll pre = -2;
    rep(i,0,k){
        if(pre+1==a[i])cnt++;
        else cnt = 1;
        if(cnt>=m){
            cout<<-1<<endl;
            return 0;
        }
        pre=a[i];
    }
    SegTree<S> seg(n+m,fx,ex);
    seg.update(0,{1,0});
    rep(i,1,n+m){
        S q = seg.query(max(0LL,i-m),min(n,i));
        rep(j,0,k){
            if(i-m<=a[j] && a[j]<i){
                q.prob-=seg.get(a[j]).prob;
                q.exp-=seg.get(a[j]).exp;
            }
        }
        q.prob/=m;
        q.exp/=m;
        q.exp+=q.prob;
        seg.update(i,q);
    }
    S goal = seg.query(n,n+m);
    S start = {0,0};
    rep(i,0,k){
        start.prob+=seg.get(a[i]).prob;
        start.exp+=seg.get(a[i]).exp;
    }
    double ans = goal.exp/goal.prob;
    if(start.prob>0) ans+=(1.0/goal.prob-1)*(start.exp/start.prob);
    cout<<ans<<endl;
    // rep(i,0,n+m)cout<<seg.get(i).prob<<" ";
    // cout<<endl;
    // rep(i,0,n+m)cout<<seg.get(i).exp<<" ";
    // cout<<endl;
    return 0;
}