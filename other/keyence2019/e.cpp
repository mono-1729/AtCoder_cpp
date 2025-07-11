#include <bits/stdc++.h>
#include <stdlib.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define inr(l, x, r) (l <= x && x < r)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define all(x) (x).begin(), (x).end()
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

ll powMod(ll x, ll n, ll mod) {
    if (n == 0) return 1 % mod;
    ll val = powMod(x, n / 2, mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
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
    ll n, d; cin >> n >> d;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    if(n == 1){
        cout << 0 << endl;
        return 0;
    }
    vector<ll> minl(n,-1), minr(n,-1);
    {
        minl[1] = 0;
        rep(i,2,n){
            if(a[i-1]+d < a[minl[i-1]]+d*(i-minl[i-1])) minl[i] = i-1;
            else minl[i] = minl[i-1];
        }
        minr[n-2] = n-1;
        rrep(i,n-3,0){
            if(a[i+1]+d*(i+1) < a[minr[i+1]]+d*(minr[i+1])) minr[i] = i+1;
            else minr[i] = minr[i+1];
        }
    }
    UnionFind uf(n);
    ll ans = 0;
    while(uf.size(0) != n){
        vector<pll> edges;
        ll now = 0;
        while(now < n){
            ll lx = now, rx = now;
            ll l = now, r = uf.max(now);
            rep(i,now,uf.max(now)+1){
                if(a[i]+d*(n-i) < a[lx]+d*(n-lx)) lx = i;
                if(a[i]+d*i < a[rx]+d*rx) rx = i;
            }
            if(l == 0) edges.emplace_back(lx,minr[r]);
            else if(r == n-1) edges.emplace_back(rx,minl[l]);
            else{
                // cout << l << " " << r << " " << minl[l] << " " << minr[r] << endl;
                if(a[rx]+a[minl[l]]+d*(rx-minl[l]) < a[lx]+a[minr[r]]+d*(minr[r]-lx)) edges.emplace_back(rx,minl[l]);
                else edges.emplace_back(lx,minr[r]);
            }
            now = r+1;
        }
        for(auto [x,y]: edges){
            if(uf.same(x,y)) continue;
            uf.unite(x,y);
            ans += a[x]+a[y]+d*abs(x-y);
            // cout << x << " " << y << " " << a[x]+a[y]+d*abs(x-y) << endl;
            // cout << ans << " " << uf.size(0) << endl;
        }
    }
    cout << ans << endl;
    return 0;
}