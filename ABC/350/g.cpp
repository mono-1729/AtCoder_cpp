#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <atcoder/all>
using namespace atcoder;
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

using mint = modint998244353;

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

class UnionFind {
    vector<ll> parent, maxi, mini;
    inline ll root(ll n){
        return (parent[n] < 0? n:parent[n] = root(parent[n]));
    }
public:
    UnionFind(ll n_ = 1): parent(n_, -1), maxi(n_), mini(n_){
        iota(maxi.begin(), maxi.end(), 0);
        iota(mini.begin(), mini.end(), 0);
    }

    inline bool same(ll x, ll y){
        return root(x) == root(y);
    }

    inline void unite(ll x, ll y){
        ll rx = root(x);
        ll ry = root(y);
        if(rx == ry) return;
        if(parent[rx] > parent[ry]) swap(rx, ry);
        parent[rx] += parent[ry];
        parent[ry] = rx;
        maxi[rx] = std::max(maxi[rx],maxi[ry]);
        mini[rx] = std::min(mini[rx],mini[ry]);
    }

    inline ll min(ll x){
        return mini[root(x)];
    }

    inline ll max(ll x){
        return maxi[root(x)];
    }

    inline ll size(ll x){
        return (-parent[root(x)]);
    }

    inline ll operator[](ll x){
        return root(x);
    }

    inline void print(){
        rep(i, 0, (ll)parent.size()) cout << root(i) << " ";
        cout << endl;
    }

    void clear(){
        rep(i, 0, (ll)parent.size()){
            parent[i] = -1;
        }
        iota(maxi.begin(), maxi.end(), 0);
        iota(mini.begin(), mini.end(), 0);
    }
};

int main() {
    int n,q;cin>>n>>q;
    vector<ll> par(n+1,n);
    vector<vector<ll>> g(n);
    UnionFind uf(n);
    ll x = 0;
    auto dfs = [&](auto dfs, ll v, ll p) -> void{
        par[v] = p;
        for(auto nv : g[v]){
            if(nv == p) continue;
            dfs(dfs,nv,v);
        }
    };
    rep(_,0,q){
        ll A,B,C;cin>>A>>B>>C;
        int a = 1LL+(((A*(1+x))%MOD)%2), b = (((B*(1+x))%MOD)%n), c = (((C*(1+x))%MOD)%n);
        //cout<<a<<" "<<b<<" "<<c<<endl;
        if(a==1){
            if(uf.size(b) < uf.size(c)) swap(b,c);
            dfs(dfs,c,b);
            uf.unite(b,c);
            g[b].push_back(c);
            g[c].push_back(b);
        }if(a==2){
            ll ans = 0;
            if(par[par[b]] == c) ans=par[b]+1;
            else if(par[par[c]] == b) ans=par[c]+1 ;
            else if(par[c] == par[b] && par[c]!=n) ans=par[c]+1;
            cout<<ans<<endl;
            x = ans;
        }

    }
    return 0;
}