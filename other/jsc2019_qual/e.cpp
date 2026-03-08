#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <stdlib.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define inr(l, x, r) (l <= x && x < r)
#define ll long long
#define ld long double
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
    if(b == 0) return a;
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
    vector<ll> parent, sum_;
    inline ll root(ll n){
        return (parent[n] < 0? n:parent[n] = root(parent[n]));
    }
public:
    UnionFind(ll n_ = 1): parent(n_, -1), sum_(n_){
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
        sum_[rx] = sum_[rx]+sum_[ry];
    }
    inline ll sum(ll x){
        return sum_[root(x)];
    }

    inline ll plus(ll x){
        return sum_[root(x)]++;
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
    }

    vector<vector<ll>> groups(){
        ll n = parent.size();
        vector<vector<ll>> res(n);

        rep(i,0,n){
            res[root(i)].push_back(i);
        }

        vector<vector<ll>> ret;
        rep(i,0,n){
            if(!res[i].empty()) ret.push_back(res[i]);
        }

        return ret;
    }
};


int main() {
    ll n, h, w;cin >> n >> h >> w;
    vector<tuple<ll,ll,ll>> vec(n);
    rep(i,0,n){
        ll r, c, a; cin >> r >> c >> a;
        r--;c--;
        vec[i] = {a,r,h+c};
    }
    sort(all(vec), greater<tuple<ll,ll,ll>>());
    ll ans = 0;
    UnionFind uf(h+w);
    for(auto [a,r,c]: vec){
        if(uf[r] == uf[c]){
            if(uf.sum(uf[r]) < uf.size(uf[r])){
                uf.plus(r);
                ans += a;
            }
        }else{
            if(uf.sum(uf[r])+uf.sum(uf[c]) < uf.size(uf[r])+uf.size(uf[c])){
                uf.plus(r);
                uf.unite(r,c);
                ans += a;
            }
        }
    }
    cout << ans << endl;
    return 0;
}