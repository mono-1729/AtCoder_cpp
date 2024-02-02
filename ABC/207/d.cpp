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
    if(n==1){
        cout<<"Yes"<<endl;
        return 0;
    }
    vector<pll> pos1(n), pos2(n);
    unordered_map<ll, ll> mp;
    rep(i, 0, n) cin>>pos1[i].first>>pos1[i].second;
    rep(i, 0, n) cin>>pos2[i].first>>pos2[i].second;
    rep(i,1,n){
        pos1[i].first -= pos1[0].first;
        pos1[i].second -= pos1[0].second;
        mp[pos1[i].first*1e5+pos1[i].second]=1;
    }
    pos1[0]={0,0};
    mp[0]=1;
    rep(i,0,n){
        rep(j,0,n){
            if(i==j) continue;
            pos2[j].first -= pos2[i].first;
            pos2[j].second -= pos2[i].second;
        }
        pos2[i]={0,0};
        rep(j,0,n){
            if(i==j) continue;
            ll x1=pos2[j].first, y1=pos2[j].second, x2=pos1[1].first, y2=pos1[1].second;
            if(x1*x1+y1*y1!=x2*x2+y2*y2) continue;
            double angle = atan2(y2,x2)-atan2(y1,x1);
            bool flag=true;
            rep(k,0,n){
                ll x=pos2[k].first, y=pos2[k].second;
                double nx=cos(angle)*x-sin(angle)*y;
                double ny=sin(angle)*x+cos(angle)*y;
                ll nx2=round(nx), ny2=round(ny);
                if(abs(nx-nx2)>1e-6 || abs(ny-ny2)>1e-6){
                    flag=false;
                    break;
                }
                if(mp[nx2*1e5+ny2]==0){
                    flag=false;
                    break;
                }
            }
            if(flag){
                cout<<"Yes"<<endl;
                //cout<<i<<" "<<j<<" "<<sin.first<<" "<<sin.second<<" "<<cos.first<<" "<<cos.second<<endl;
                return 0;
            }            
        }
    }
    cout<<"No"<<endl;
    return 0;
}