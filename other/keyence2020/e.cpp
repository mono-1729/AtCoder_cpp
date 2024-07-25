#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <atcoder/all>
using namespace atcoder;
using namespace boost::multiprecision;
using namespace std;
#define rep(i, a, n) for(int i = a; i < n; i++)
#define rrep(i, a, n) for(int i = a; i >= n; i--)
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
    int n, m; cin >> n >> m;
    vector<int> d(n);
    rep(i,0,n) cin >> d[i];
    string s = string(n,'x');
    vector<int> weight(m,-1);
    vector<tuple<int,int,int,int>> edges(m);
    rep(i,0,m){
        int u, v; cin >> u >> v;
        u--; v--;
        if(d[u] > d[v]) swap(u, v);
        edges[i] = {max(d[u],d[v]), i, u, v};
    }
    sort(edges.begin(), edges.end());
    for(auto[max_d,idx,u,v]: edges){
        if(s[u] == 'x' && s[v] == 'x'){
            if(d[u] != d[v]){
                cout << -1 << endl;
                return 0;
            }
            s[u] = 'B', s[v] = 'W';
            weight[idx] = d[u];
        }else if(s[u] == 'x'){
            if(d[u] != d[v]){
                cout << -1 << endl;
                return 0;
            }
            s[u] = s[v] == 'W' ? 'B' : 'W';
            weight[idx] = d[u];
        }else if(s[v] == 'x'){
            s[v] = s[u] == 'W' ? 'B' : 'W';
            weight[idx] = d[v];
        }else{
            weight[idx] = (int)1e9;
        }
    }
    cout << s << endl;
    rep(i,0,m) cout << weight[i] << endl;
    return 0;
}