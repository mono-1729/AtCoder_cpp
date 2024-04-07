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
    ll h,w;cin>>w>>h;
    vector<string> s(h);
    rep(i,0,h)cin>>s[i];
    vector<vector<ll>> dist1(h,vector<ll>(w,INF)),dist2(h,vector<ll>(w,INF));
    ll x1,y1,x2,y2;
    rep(i,0,h)rep(j,0,w){
        if(s[i][j]=='1'){
            x1 = i;
            y1 = j;
        }
        if(s[i][j]=='2'){
            x2 = i;
            y2 = j;
        }
    }
    queue<pll> q;
    q.push({x1,y1});
    dist1[x1][y1] = 0;
    while(!q.empty()){
        ll x = q.front().first;
        ll y = q.front().second;
        q.pop();
        if(x>0 && s[x-1][y]!='#'){
            if(dist1[x-1][y]>dist1[x][y]+1){
                dist1[x-1][y] = dist1[x][y]+1;
                q.push({x-1,y});
            }
        }
        if(x<h-1 && s[x+1][y]!='#'){
            if(dist1[x+1][y]>dist1[x][y]+1){
                dist1[x+1][y] = dist1[x][y]+1;
                q.push({x+1,y});
            }
        }
        if(y>0 && s[x][y-1]!='#'){
            if(dist1[x][y-1]>dist1[x][y]+1){
                dist1[x][y-1] = dist1[x][y]+1;
                q.push({x,y-1});
            }
        }
        if(y<w-1 && s[x][y+1]!='#'){
            if(dist1[x][y+1]>dist1[x][y]+1){
                dist1[x][y+1] = dist1[x][y]+1;
                q.push({x,y+1});
            }
        }
    }
    q.push({x2,y2});
    dist2[x2][y2] = 0;
    while(!q.empty()){
        ll x = q.front().first;
        ll y = q.front().second;
        q.pop();
        if(x>0 && s[x-1][y]!='#'){
            if(dist2[x-1][y]>dist2[x][y]+1){
                dist2[x-1][y] = dist2[x][y]+1;
                q.push({x-1,y});
            }
        }
        if(x<h-1 && s[x+1][y]!='#'){
            if(dist2[x+1][y]>dist2[x][y]+1){
                dist2[x+1][y] = dist2[x][y]+1;
                q.push({x+1,y});
            }
        }
        if(y>0 && s[x][y-1]!='#'){
            if(dist2[x][y-1]>dist2[x][y]+1){
                dist2[x][y-1] = dist2[x][y]+1;
                q.push({x,y-1});
            }
        }
        if(y<w-1 && s[x][y+1]!='#'){
            if(dist2[x][y+1]>dist2[x][y]+1){
                dist2[x][y+1] = dist2[x][y]+1;
                q.push({x,y+1});
            }
        }
    }
    ll ans = 1;
    rep(i,0,h)rep(j,0,w){
        if(dist1[i][j]>dist2[i][j]+1){
            chmax(ans,dist1[i][j]);
            //cout<<i<<" "<<j<<" "<<dist1[i][j]<<" "<<dist2[i][j]<<endl;
        }
    }
    cout<<ans<<endl;
    return 0;
}