#include <bits/stdc++.h>
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
    if (n == 0) return 1;
    ll val = powMod(x, n / 2);
    val *= val;
    if (n % 2 == 1) val *= x;
    return val;
}

int main() {
    ll n;cin>>n;
    vector<vector<ll>> g(n);
    rep(i,0,n-1){
        ll a,b;cin>>a>>b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<vector<ll>> lca(n,vector<ll>(n,-1));
    vector<vector<ll>> childs(n);
    auto dfs = [&](auto& dfs, ll now, ll par) -> vector<ll>{
        for(ll next: g[now]){
            if(next == par)continue;
            vector<ll> cds =dfs(dfs,next,now);
            childs[now].insert(childs[now].end(),cds.begin(),cds.end());
        }
        childs[now].push_back(now);
        for(ll c1: childs[now])for(ll c2: childs[now]) if(lca[c1][c2]==-1)lca[c1][c2] = now;
        return childs[now];
    };
    dfs(dfs,0,-1);
    ll m;cin>>m;
    vector<ll> u(m),v(m);
    rep(i,0,m){
        cin>>u[i]>>v[i];
        u[i]--;v[i]--;
    }
    ll ans=0;
    rep(i,0,1<<m){
        ll cnt=0;
        vector<ll> used(n,0);
        rep(j,0,m){
            if((i>>j)&1){
                cnt++;
                used[u[j]]+=1;
                used[v[j]]+=1;
                used[lca[u[j]][v[j]]]-=2;
            }
        }
        ll tmp=n-1;
        auto dfs2 = [&](auto& dfs2, ll now, ll par) -> ll{
            for(ll next: g[now]){
                if(next == par)continue;
                ll num=dfs2(dfs2,next,now);
                used[now]+=num;
            }
            if(used[now]>0)tmp--;
            return used[now];
        };
        dfs2(dfs2,0,-1);
        if(cnt%2==0)ans+=powMod(2,tmp);
        else ans-=powMod(2,tmp);
    }
    cout<<ans<<endl;
    return 0;
}