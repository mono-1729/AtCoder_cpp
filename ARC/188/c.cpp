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
    UnionFind uf(n*2);
    vector<tuple<ll,ll,ll>> query;
    rep(i,0,m){
        ll a, b, c; cin >> a >> b >> c;
        a--; b--;
        query.push_back({a,b,c});
    }
    sort(query.begin(), query.end());
    rep(i,0,m-1){
        auto [a1, b1, c1] = query[i];
        auto [a2, b2, c2] = query[i+1];
        if(a1 == a2){
            if(c1 == c2){
                uf.unite(b1, b2);
                uf.unite(b1+n, b2+n);
            }else{
                uf.unite(b1, b2+n);
                uf.unite(b1+n, b2);
            }
        }
    }
    rep(i,0,n){
        if(uf.same(i, i+n)){
            cout << "-1" << endl;
            return 0;
        }
    }
    vector<vector<ll>> group(n);
    rep(i,0,n){
        group[min(uf[i], uf[i+n])].push_back(i);
    }
    vector<ll> lier(n, -1), confuse(n, 0);
    rep(i,0,n){
        if(group[i].size() == 0) continue;
        lier[group[i][0]] = 1;
        rep(j,1,(ll)group[i].size()){
            if(uf.same(group[i][0], group[i][j])){
                lier[group[i][j]] = 1;
            }else{
                lier[group[i][j]] = 0;
            }
        }
    }
    for(auto [a,b,c]: query){
        if(lier[a] == 0){
            if(lier[b] == c) confuse[a] = 0;
            else confuse[a] = 1;
        }else{
            if(lier[b] == c) confuse[a] = 1;
            else confuse[a] = 0;
        }
    }
    rep(i,0,n) cout << confuse[i];
    cout << endl;
    return 0;
}