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
    ll n;cin>>n;
    vector<ll> p(n);
    rep(i,0,n) cin >> p[i];
    vector<ll> num(n,1);
    vector<ll> pos(n+1);
    rep(i,0,n) pos[p[i]] = i;
    set<ll> s;
    vector<ll> ans(n);
    rep(i,0,n-1){
        s.insert(i);
    }
    rep(i,1,n+1){
        if(s.find(pos[i]) != s.end()) s.erase(pos[i]);
        if(s.find(pos[i]-1) != s.end()) s.erase(pos[i]-1);
        ll x = INF;
        ll ps = pos[i];
        if(ps!=0 && ps != n-1 && num[ps-1] + num[ps+1] != 0) x = 3;
        if(s.size() != 0){
            auto it = s.lower_bound(ps);
            if(it != s.end()){
                chmin(x,((*it - ps + 2)/2)*2+1);
            }
            if(it != s.begin()){
                it--;
                chmin(x,((ps - *it + 1)/2)*2+1);
            }
        }
        if(ps==0){
            x=INF;
            ll z = 0;
            ll idx = 0;
            while(idx+2<n){
                z+=num[idx+1];
                z+=num[idx+2];
                if(z!=0){
                    chmin(x,idx+3);
                    break;
                }
                idx+=2;
            }
        }else if(ps==n-1){
            x = INF;
            ll z = 0;
            ll idx = n-1;
            while(idx-2>=0){
                z+=num[idx-1];
                z+=num[idx-2];
                if(z!=0){
                    chmin(x,n-idx+2);
                    break;
                }
                idx-=2;
            }
        }
        if(x==INF) ans[ps] = -1;
        else ans[ps] = x;
        num[ps]=-1;
        if(ps!=0 && num[ps-1] == -1)s.insert(ps-1);
        if(ps!=n-1 && num[ps+1] == -1)s.insert(ps);
    }
    rep(i,0,n) cout << ans[i] << " ";
    cout << endl;
    return 0;
}