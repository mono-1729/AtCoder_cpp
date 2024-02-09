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
    ll h,w;cin>>h>>w;
    vector<vector<ll>> s(h, vector<ll>(w));
    rep(i,0,h)rep(j,0,w)cin>>s[i][j];
    bool flag = true;
    rep(i,0,h)rep(j,0,w){
        if(s[i][j] != i*w+j+1) flag = false;
    }
    if(flag){
        cout << 0 << endl;
        return 0;
    }
    auto rotate = [&](vector<vector<ll>>& v, ll u, ll l)->void{
        vector<vector<ll>> tmp(h, vector<ll>(w));
        rep(i,0,h)rep(j,0,w)tmp[i][j] = v[i][j];
        rep(i,0,h-1)rep(j,0,w-1){
            v[i+u][j+l] = tmp[h-i+u-2][w-j+l-2];
        }
    };
    map<vector<vector<ll>>,ll>mp,mp2;
    vector<vector<vector<ll>>> vecs;
    vecs.push_back(s);
    rep(_,1,11){
        vector<vector<vector<ll>>> new_vecs;
        for(auto vec:vecs){
            rep(x,0,2)rep(y,0,2){
                rotate(vec, x, y);
                if(mp[vec] == 0){
                    mp[vec] = _;
                    new_vecs.push_back(vec);
                }
                rotate(vec, x, y);
            }
        }
        swap(vecs, new_vecs);
    }
    vector<vector<ll>> nomal(h, vector<ll>(w));
    rep(i,0,h)rep(j,0,w)nomal[i][j] = i*w+j+1;
    if(mp[nomal] != 0){
        cout << mp[nomal] << endl;
        return 0;
    }
    vecs.clear();
    vecs.push_back(nomal);
    rep(_,1,11){
        vector<vector<vector<ll>>> new_vecs;
        for(auto vec:vecs){
            rep(x,0,2)rep(y,0,2){
                rotate(vec, x, y);
                if(mp2[vec] == 0){
                    mp2[vec] = _;
                    new_vecs.push_back(vec);
                }
                rotate(vec, x, y);
            }
        }
        swap(vecs,new_vecs);
    }
    ll ans = 100;
    for(auto p:mp2){
        vector<vector<ll>> tmp= p.first;
        if(mp[tmp] != 0){
            chmin(ans, mp[tmp]+p.second);
        } 
    }
    if(ans == 100) cout << -1 << endl;
    else cout << ans << endl;
    return 0;
}