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
    ll h, w; cin >> h >> w;
    vector<vector<ll>> f(h, vector<ll>(w));
    rep(i,0,h)rep(j,0,w) cin >> f[i][j];
    ll q; cin >> q;
    vector<ll> a(q), b(q), y(q), c(q), d(q), z(q);
    rep(i,0,q){
        cin >> a[i] >> b[i] >> y[i] >> c[i] >> d[i] >> z[i];
        a[i]--, b[i]--, c[i]--, d[i]--;
    }
    vector<tuple<ll,ll,ll>> query(h*w);
    rep(i,0,h)rep(j,0,w){
        query[i*w+j] = {f[i][j], i, j};
    }
    sort(all(query), greater<tuple<ll,ll,ll>>());
    vector<ll> ng(q, -1), ok(q, h*w-1);
    vector<ll> dx = {-1, 1, 0, 0}, dy = {0, 0, 1, -1};

    rep(_,0,20){
        vector<vector<ll>> judge(h*w);
        rep(i,0,q){
            ll mid = (ok[i]+ng[i])/2;
            judge[mid].push_back(i);
        }
        UnionFind uf(h*w);
        rep(i,0,h*w){
            auto [ff, xx, yy] = query[i];
            rep(j,0,4){
                ll nx = xx+dx[j], ny = yy+dy[j];
                if(nx < 0 || ny < 0 || nx >= h || ny >= w) continue;
                if(f[xx][yy] > f[nx][ny]) continue;
                uf.unite(xx*w+yy, nx*w+ny);
            }
            for(auto id: judge[i]){
                if(uf.same(a[id]*w+b[id], c[id]*w+d[id])) ok[id] = i;
                else ng[id] = i;
            }
        }
    }

    rep(i,0,q){
        ll height = get<0>(query[ok[i]]);
        // cout << ok[i] << " ";
        // cout << height << " ";
        chmin(height, y[i]);
        chmin(height, z[i]);
        cout << y[i] + z[i] - 2*height << endl;
    }

    return 0;
}