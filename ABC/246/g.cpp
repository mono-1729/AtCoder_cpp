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
    ll n; cin >> n;
    vector<ll> a(n-1);
    rep(i,0,n-1) cin >> a[i];
    vector<vector<ll>> g(n);
    vector<ll> par1(n),par2(n);
    rep(i,0,n-1){
        ll u,v; cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    auto init = [&](auto self, ll v, ll p) -> void {
        par1[v] = p;
        par2[v] = p;
        for(auto nv: g[v]){
            if(nv == p) continue;
            self(self, nv, v);
        }
    };
    init(init,0,-1);
    vector<pll> pa(n-1);
    vector<ll> used(n,0);
    rep(i,0,n-1) pa[i] = {a[i],i+1};
    sort(pa.begin(), pa.end(), greater<pll>());
    pa.push_back({0,-1});
    UnionFind uf(n);
    auto add = [&](ll u) -> bool {
        u = par1[u];
        if(used[u]){
            if(par2[uf[u]] == -1) return false;
            u = par2[uf[u]];
        }
        used[u] = 1;
        for(auto v:g[u]){
            if(used[v] == 1){
                if(v == par1[u]){
                    ll tmp = par2[uf[v]];
                    uf.unite(u,v);
                    par2[uf[u]] = tmp;
                }
                else{
                    ll tmp = par2[uf[u]];
                    uf.unite(u,v);
                    par2[uf[u]] = tmp;
                }
            }
        }
        return true;
    };
    ll ans = pa[0].first;
    rep(i,0,n-1){
        auto [a,idx] = pa[i];
        if(!add(idx)) break;
        else ans = pa[i+1].first;
        // for(auto x: used) cout << x << " " ;
        // cout << endl;
    }
    cout << ans << endl;
    return 0;
}