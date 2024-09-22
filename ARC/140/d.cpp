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
    vector<ll> parent, maxi, mini, have;
    inline ll root(ll n){
        return (parent[n] < 0? n:parent[n] = root(parent[n]));
    }
public:
    UnionFind(ll n_ = 1): parent(n_, -1), maxi(n_), mini(n_), have(n_){
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
        have[rx] = std::max(have[rx],have[ry]);
        maxi[rx] = std::max(maxi[rx],maxi[ry]);
        mini[rx] = std::min(mini[rx],mini[ry]);
    }

    inline ll min(ll x){
        return mini[root(x)];
    }
    
    void update_have(ll i){have[root(i)] = 1;}

    ll get_have(ll i){return have[root(i)];}


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
    vector<ll> a(n); vector<mint> fac(n+1,1);
    rep(i,0,n) cin >> a[i], a[i]--;
    rep(i,1,n+1) fac[i] = fac[i-1] * i;
    mint ans = 0;
    ll m = 0;
    UnionFind uf(n);
    rep(i,0,n){
        if(a[i] == -2){
            uf.update_have(i);
            continue;
        }else uf.unite(i,a[i]);
    }
    queue<vector<mint>> que; que.push({1}); 
    rep(i,0,n)if(uf[i] == i && uf.get_have(i)){
        m++;
        que.push({1,uf.size(i)});
    }
    rep(i,0,n)if(uf[i] == i && !uf.get_have(i)) ans += powMod(n,m);
    while(que.size() >= 2){
        vector<mint> v1, v2;
        v1 = que.front();que.pop();
        v2 = que.front();que.pop();
        que.push(convolution(v1,v2));
    }
    vector<mint> dp = que.front();
    rep(i,1,m+1) ans += dp[i] * fac[i-1] * powMod(n,m-i);

    cout << ans.val() << endl;
    return 0;
}