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
    ll n,m;cin>>n>>m;
    vector<unordered_set<ll>>g(n);
    rep(i,0,n)rep(j,0,n){
        if(i==j)continue;
        g[i].insert(j);
    }
    UnionFind uf(n);
    rep(i,0,m){
        ll a,b;cin>>a>>b;
        a--;b--;
        g[a].erase(b);
        g[b].erase(a);
    }
    rep(i,0,n)for(auto j:g[i]){
        uf.unite(i,j);
    }
    ll sum = 0;
    vector<ll> size;
    vector<ll> dist(n,-1);
    rep(i,0,n){
        if(uf[i]!=i) continue;
        ll n0 = 1,n1 = 0;
        queue<ll> q;
        q.push(i);
        dist[i] = 0;
        while(!q.empty()){
            ll v = q.front();q.pop();
            for(auto nv:g[v]){
                if(dist[nv]==-1){
                    dist[nv]=dist[v]+1;
                    q.push(nv);
                    if(dist[nv]%2==0)n0++;
                    else n1++;
                }
                else if(dist[v]%2 == dist[nv]%2){
                    //cout<<v<<" "<<nv<<" "<<dist[v]<<" "<<dist[nv]<<endl;
                    cout<<-1<<endl;
                    return 0;
                }
            }
        }
        sum+=min(n0,n1);
        size.push_back(max(n0,n1)-min(n0,n1));
    }
    ll l = size.size();
    vector<vector<ll>> dp(l+1,vector<ll>(n/2+1,0));
    dp[0][sum]=1;
    rep(i,0,l)rep(j,0,n/2+1){
        chmax(dp[i+1][j],dp[i][j]);
        if(j+size[i]<=n/2)chmax(dp[i+1][j+size[i]],dp[i][j]);
    }
    ll ma = 0;
    rep(i,0,n/2+1)if(dp[l][i]==1)chmax(ma,i);
    cout<<ma*(ma-1)/2+(n-ma)*(n-ma-1)/2<<endl;
    //cout<<ma<<endl;
    return 0;
}