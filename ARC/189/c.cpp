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

using S = long long;
S op(S x1, S x2) {
    return max(x1, x2);
} 
S e() {return 0;}

int main() {
    ll n, x; cin >> n >> x;
    x--;
    vector<ll> a(n), b(n), p(n), q(n);
    UnionFind uf1(n), uf2(n);
    ll asum = 0, bsum = 0;
    rep(i,0,n) cin >> a[i], asum += a[i];
    rep(i,0,n) cin >> b[i], bsum += b[i];
    rep(i,0,n) cin >> p[i], p[i]--, uf1.unite(i, p[i]);
    rep(i,0,n) cin >> q[i], q[i]--, uf2.unite(i, q[i]);

    {
        vector<ll> pp(n), qq(n);
        rep(i,0,n) pp[p[i]] = i;
        rep(i,0,n) qq[q[i]] = i;
        rep(i,0,n) p[i] = pp[i], q[i] = qq[i];
    }
    
    bool ok = true;
    rep(i,0,n){
        if(a[i] && !uf1.same(i, x)) ok = false;
        if(b[i] && !uf2.same(i, x)) ok = false;
    }

    if(!ok){
        cout << -1 << endl;
        return 0;
    }

    ll id = 1;
    unordered_map<ll,ll> mp;
    ll acnt = a[x], bcnt = b[x];
    ll alen = 0, blen = 0;
    {
        ll now = x;
        while(acnt < asum){
            now = p[now];
            acnt += a[now];
            mp[now] = id;
            alen++;
            id++;
        }
    }

    segtree<S, op, e> seg(id);
    {
        ll now = x;
        while(bcnt < bsum){
            now = q[now];
            bcnt += b[now];
            blen++;
            if(mp[now]){
                seg.set(mp[now], seg.prod(0, mp[now]) + 1);
            }
        }
    }

    cout << alen + blen - seg.all_prod() << endl;
    return 0;
}