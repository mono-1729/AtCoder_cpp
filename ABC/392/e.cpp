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
    ll n, m; cin >> n >> m;
    vector<vector<pll>> me(n);
    auto marge = [&](ll a, ll b)-> void {
        ll f = 0;
        if(me[a].size() < me[b].size()){
            swap(me[a], me[b]);
            f = 1;
        }
        for(auto x: me[b]){
            me[a].push_back(x);
        }
        if(f) swap(me[a], me[b]);
    };
    UnionFind uf(n);
    rep(i,0,m){
        ll a, b; cin >> a >> b;
        a--;b--;
        if(uf.same(a, b)){
            me[uf[a]].push_back({i, b});
        }else{
            ll na = uf[a], nb = uf[b];
            marge(na, nb);
            uf.unite(a, b);
            ll np = uf[a];
            if(me[np].size() == 0) swap(me[na], me[nb]);
        }
    }
    set<pll> st;
    vector<tuple<ll,ll,ll>> ans;
    rep(i,0,n){
        if(uf[i] == i){
            st.insert({me[i].size(), i});
        }
    }
    while(st.size() > 1){
        auto [_, a] = *st.rbegin();
        st.erase(prev(st.end()));
        auto [__, b] = *st.rbegin();
        st.erase(prev(st.end()));
        auto [i, x] = me[a].back();
        me[a].pop_back();
        ans.push_back({i, x, b});
        ll na = uf[a], nb = uf[b];
        marge(na, nb);
        uf.unite(a, b);
        ll np = uf[a];
        if(me[np].size() == 0) swap(me[na], me[nb]);
        st.insert({me[np].size(), np});
    }
    cout << ans.size() << endl;
    for(auto [x,y,z]: ans){
        cout << x+1 << " " << y+1 << " " << z+1 << endl;
    }

    return 0;
}