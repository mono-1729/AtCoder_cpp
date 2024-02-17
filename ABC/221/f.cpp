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
    vector<vector<ll>> g(n);
    rep(i,0,n-1){
        ll a,b;cin>>a>>b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<ll> dist(n, -1);
    queue<ll> q;
    q.push(0);
    dist[0] = 0;
    pll max_dist = {0, 0};
    while(!q.empty()){
        ll now = q.front();q.pop();
        for(auto to : g[now]){
            if(dist[to] != -1) continue;
            dist[to] = dist[now] + 1;
            if(dist[to] > max_dist.second) max_dist = {to, dist[to]};
            q.push(to);
        }
    }
    dist=vector<ll>(n, -1);
    ll start = max_dist.first;
    q.push(start);
    dist[start] = 0;
    max_dist = {0, 0};
    while(!q.empty()){
        ll now = q.front();q.pop();
        for(auto to : g[now]){
            if(dist[to] != -1) continue;
            dist[to] = dist[now] + 1;
            if(dist[to] > max_dist.second) max_dist = {to, dist[to]};
            q.push(to);
        }
    }
    if(max_dist.second%2==0){
        ll mid=-1;
        vector<ll> path;
        auto dfs = [&](auto& dfs,ll now,ll par)->void{
            path.push_back(now);
            if(now == max_dist.first){
                mid = path[path.size()/2];
            }
            for(auto to : g[now]){
                if(to == par) continue;
                dfs(dfs, to, now);
            }
            path.pop_back();
        };
        dfs(dfs, start, -1);
        mint ans = 1;
        ll sum =0;
        auto dfs2 = [&](auto& dfs2,ll now,ll par,ll d)->ll{
            ll res = 0;
            if(d == max_dist.second/2) res++;
            for(auto to : g[now]){
                if(to == par || to == mid) continue;
                res += dfs2(dfs2, to, now, d+1);
            }
            return res;
        };
        for(auto to : g[mid]){
            ll res = dfs2(dfs2, to, mid, 1);
            ans *= res+1;
            sum += res;
        }
        ans -= sum+1;
        cout << ans << endl;
    }else{
        vector<ll> path;
        ll l=-1,r=-1;
        auto dfs = [&](auto& dfs,ll now,ll par)->void{
            path.push_back(now);
            if(now == max_dist.first){
                l = path[path.size()/2-1];
                r = path[path.size()/2];
            }
            for(auto to : g[now]){
                if(to == par) continue;
                dfs(dfs, to, now);
            }
            path.pop_back();
        };
        dfs(dfs, start, -1);
        pll ml = {0, 0}, mr = {0, 0};
        auto dfs2 = [&](auto& dfs2,ll now,ll par,ll d,pll& m)->void{
            if(d > m.second) m = {1,d};
            else if(d == m.second) m.first++;
            for(auto to : g[now]){
                if(to == par) continue;
                if(to == l || to == r) continue;
                dfs2(dfs2, to, now, d+1, m);
            }
        };
        dfs2(dfs2, l, -1, 0, ml);
        dfs2(dfs2, r, -1, 0, mr);
        cout << (ml.first*mr.first)%MOD << endl;
    }
    return 0;
}