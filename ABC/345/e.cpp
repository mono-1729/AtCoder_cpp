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
    ll n,k;cin>>n>>k;
    vector<ll> c(n),v(n);
    rep(i,0,n)cin>>c[i]>>v[i];
    vector<pair<pll,pll>> dp(k+1,make_pair(make_pair(-1,-1),make_pair(-1,-1)));
    dp[0] = make_pair(make_pair(0,0),make_pair(-1,-1));
    rep(i,0,n){
        rrep(j,k,0){
            if(dp[j].first.first != -1 && j != k){
                if(dp[j+1].first.second == dp[j].first.second){
                    chmax(dp[j+1].first.first,dp[j].first.first);
                }else if(dp[j+1].second.second == dp[j].first.second){
                    chmax(dp[j+1].second.first,dp[j].first.first);
                    if(dp[j+1].second.first > dp[j+1].first.first){
                        swap(dp[j+1].second,dp[j+1].first);
                    }
                }else{
                    if(dp[j+1].first.first < dp[j].first.first){
                        dp[j+1].second = dp[j+1].first;
                        dp[j+1].first = dp[j].first;
                    }
                    else(chmax(dp[j+1].second,dp[j].first));
                }
            }
            if(dp[j].second.first != -1 && j != k){
                if(dp[j+1].second.second == dp[j].first.second){
                    chmax(dp[j+1].second.first,dp[j].second.first);
                }else{
                    if(dp[j+1].second.first < dp[j].second.first){
                        dp[j+1].second = dp[j].second;
                    }
                }
            }
            if(dp[j].first.first != -1 && dp[j].first.second != c[i]){
                dp[j].first.first += v[i];
                dp[j].first.second = c[i];
                dp[j].second={-1,-1};
            }else if(dp[j].second.first != -1 && dp[j].second.second != c[i]){
                dp[j].second.first += v[i];
                dp[j].second.second = c[i];
                dp[j].first={-1,-1};
            }else {
                dp[j].first={-1,-1};
                dp[j].second={-1,-1};
            }
            if(dp[j].first<dp[j].second)swap(dp[j].first,dp[j].second);
        }
    }
    if(dp[k].first.first==-1)cout << -1 << endl;
    else cout << dp[k].first.first << endl;
    return 0;
}