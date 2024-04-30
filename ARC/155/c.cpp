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
    ll n;cin>>n;
    vector<ll> a(n),b(n),aeven,beven;
    unordered_map<ll,vector<ll>> amp,bmp;
    rep(i,0,n) cin>>a[i];
    rep(i,0,n) cin>>b[i];
    rep(i,0,n){
        amp[a[i]].push_back(i);
        if(a[i]%2==0) aeven.push_back(a[i]);
    }
    rep(i,0,n){
        bmp[b[i]].push_back(i);
        if(b[i]%2==0) beven.push_back(b[i]);
    }
    for(auto x:amp){
        ll num = x.first;
        if(x.second.size()!=bmp[num].size()){
            cout<<"No"<<endl;
            return 0;
        }
    }
    if(aeven.size()==2)if(aeven[0]!=beven[0] || aeven[1]!=beven[1]){
        cout<<"No"<<endl;
        return 0;
    }
    vector<ll> bidx(n);
    for(auto x:bmp){
        auto vec = x.second;
        rep(i,0,vec.size()){
            bidx[vec[i]]= amp[x.first][i];
        }
    }
    UnionFind uf(n);
    bool f1a=false,f2a=false,f1b=false,f2b=false;
    rep(i,0,n-2){
        if((a[i]+a[i+1]+a[i+2])%2==0){
            if(a[i]%2==0 && a[i+1]%2==0 && a[i+2]%2==0){
                uf.unite(i,i+1);
                uf.unite(i,i+2);
                f1a=true;
            }
            else if(!f2a){
                rep(j,0,n-1)uf.unite(j,j+1);
                f2a = true;
            }
        }
    }
    rep(i,0,n-2){
        if((b[i]+b[i+1]+b[i+2])%2==0){
            if(b[i]%2==0 && b[i+1]%2==0 && b[i+2]%2==0){
                f1b=true;
            }
            else{
                f2b = true;
            }
        }
    }
    if(f2a!=f2b){
        cout<<"No"<<endl;
        return 0;
    }
    rep(i,0,n){
        if(!uf.same(i,bidx[i])){
            cout<<"No"<<endl;
            return 0;
        }
    }
    cout<<"Yes"<<endl;
    return 0;
}