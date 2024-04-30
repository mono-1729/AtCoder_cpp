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
    ll h,w;cin>>h>>w;
    vector<string> s(h);
    rep(i,0,h)cin>>s[i];
    vector<vector<ll>> check(h,vector<ll>(w,0)),zi(h,vector<ll>(w,0));;
    rep(i,0,h)rep(j,0,w){
        if(s[i][j]=='#') check[i][j] = 1;
        if(i-1>=0 && s[i-1][j]=='#') zi[i][j] = 1;
        if(i+1<h && s[i+1][j]=='#') zi[i][j] = 1;
        if(j-1>=0 && s[i][j-1]=='#') zi[i][j] = 1;
        if(j+1<w && s[i][j+1]=='#') zi[i][j] = 1;
    }
    UnionFind uf(h*w);
    vector<vector<ll>> ans(h,vector<ll>(w,0));
    vector<ll> dx = {1,0,-1,0};
    vector<ll> dy = {0,1,0,-1};
    rep(i,0,h)rep(j,0,w){
        if(check[i][j]==1 || zi[i][j]==1) continue;
        ans[i][j] = 1;
        check[i][j] = 1;
        unordered_map<ll,ll> mp;
        queue<pll> q;
        q.push({i,j});
        while(!q.empty()){
            auto [x,y] = q.front();
            q.pop();
            rep(k,0,4){
                ll nx = x+dx[k];
                ll ny = y+dy[k];
                if(nx<0 || nx>=h || ny<0 || ny>=w) continue;
                if(check[nx][ny]==1) continue;
                if(mp[nx*w+ny]!=1)ans[i][j] += 1;
                if(zi[nx][ny]!=1){
                    q.push({nx,ny});
                    check[nx][ny] = 1;
                }
                else mp[nx*w+ny] = 1;
            }  
        }
    }
    ll res = 1;
    rep(i,0,h)rep(j,0,w){
        res = max(res,ans[i][j]);
    }
    cout<<res<<endl;
    return 0;
}