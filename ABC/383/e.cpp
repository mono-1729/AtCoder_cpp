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
    ll n, m, k; cin >> n >> m >> k;
    UnionFind uf(n);
    vector<tuple<ll, ll, ll>> uvw(m);
    rep(i,0,m){
        ll u, v, w; cin >> u >> v >> w;
        u--; v--;
        uvw[i] = {u, v, w};
    }
    sort(uvw.begin(), uvw.end(), [](auto a, auto b){
        return get<2>(a) < get<2>(b);
    });
    vector<ll> ga(n), gb(n);
    rep(i,0,k){
        ll a; cin >> a;
        a--;
        ga[a]++;
    }
    rep(i,0,k){
        ll b; cin >> b;
        b--;
        gb[b]++;
    }
    ll ans = 0;
    for(auto [u, v, w]: uvw){
        if(uf.same(u, v)) continue;
        ll gas = ga[uf[u]]+ga[uf[v]], gbs = gb[uf[u]]+gb[uf[v]];
        ga[uf[u]] = ga[uf[v]] = 0;
        gb[uf[u]] = gb[uf[v]] = 0;
        uf.unite(u, v);
        ll x = min(gas, gbs);
        ans += x*w;
        ga[uf[u]] = gas-x;
        gb[uf[u]] = gbs-x;
    }
    cout << ans << endl;

    return 0;
}