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

struct st {
    ll l;
    ll r;
    vector<pll> bros;
    st(ll l, ll r, vector<pll> bros = {}) : l(l), r(r), bros(bros){};
};

int main() {
    ll n, m; cin >> n >> m;
    ll base = 100005, base2 = base*base;
    vector<ll> a(m), b(m);
    rep(i,0,m) cin >> a[i] >> b[i], a[i]--, b[i]--;
    ll q; cin >> q;
    vector<ll> ans(q);
    vector<st> nowst;
    nowst.push_back(st(-1,m));
    rep(i,0,q){
        ll x, y, z; cin >> x >> y >> z;
        x--;y--;
        nowst.back().bros.push_back({x*base2+y*base+z,i});
    }
    while(nowst.size()){
        vector<st> nextst;
        // rep(i,0,nowst.size()-1){
        //     assert(nowst[i].r <= nowst[i+1].l);
        // }
        UnionFind uf(n);
        ll next = 0;
        for(auto [l, r, bros] : nowst){
            ll mid = (l+r)/2;
            rep(i, next, mid+1) uf.unite(a[i], b[i]);
            vector<pll> lbro, rbro;
            for(auto [num,id]: bros){
                ll x = num/base2, y = (num%base2)/base, z = num%base;
                if(uf.same(x,y)){
                    if(uf.size(x) >= z) lbro.push_back({num,id});
                    else rbro.push_back({num,id});
                }else{
                    if(uf.size(x) + uf.size(y) >= z) lbro.push_back({num,id});
                    else rbro.push_back({num,id});
                }
            }
            next = mid+1;
            if(mid-l>1) nextst.push_back(st(l,mid,lbro));
            else for(auto [num,id] : lbro) ans[id] = mid+1;
            if(r-mid>1) nextst.push_back(st(mid,r,rbro));
            else for(auto [num,id] : rbro) ans[id] = r+1;
        }
        swap(nowst, nextst);
    }
    for(auto x: ans) cout << x << endl;
    return 0;
}