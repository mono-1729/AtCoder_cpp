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
    ll n, q; cin >> n >> q;
    vector<vector<ll>> vec(n);
    rep(i,0,n) vec[i].push_back(i+1);
    UnionFind uf(n);
    while(q--){
        ll type; cin >> type;
        if(type == 1){
            ll u, v; cin >> u >> v;
            u--;v--;
            ll pu = uf[u], pv = uf[v];
            if(pu == pv) continue;
            uf.unite(u, v);
            ll np = uf[u];
            if(vec[pu].size() > vec[pv].size()){
                for(auto x: vec[pv]) vec[pu].push_back(x);
                sort(vec[pu].begin(), vec[pu].end(), greater<ll>());
                if(vec[pu].size() > 10)vec[pu].resize(10);
                swap(vec[np], vec[pu]);
            }else{
                for(auto x: vec[pu]) vec[pv].push_back(x);
                sort(vec[pv].begin(), vec[pv].end(), greater<ll>());
                if(vec[pv].size() > 10)vec[pv].resize(10);
                swap(vec[np], vec[pv]);
            }
        }
        if(type == 2){
            ll v, k; cin >> v >> k;
            v--;
            if(vec[uf[v]].size() < k) cout << -1 << endl;
            else cout << vec[uf[v]][k-1] << endl;
        }
    }


    return 0;
}