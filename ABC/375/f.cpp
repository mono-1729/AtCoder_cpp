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

int main() {
    ll n, m, q; cin >> n >> m >> q;
    vector<ll> a(m), b(m), c(m);
    rep(i,0,m) cin >> a[i] >> b[i] >> c[i], a[i]--, b[i]--;
    vector<tuple<ll, ll, ll>> query(q);
    vector<ll> crush(m, 0);
    rep(i,0,q){
        ll type; cin >> type;
        if(type == 1){
            ll x; cin >> x;
            x--;
            query[i] = {type, x, 0};
            crush[x] = 1;
        }else{
            ll x, y; cin >> x >> y;
            x--; y--;
            query[i] = {type, x, y};
        }
    }
    vector<ll> ans(q, INF);
    vector<vector<ll>> dist(n, vector<ll>(n, INF));
    rep(i,0,m){
        if(crush[i] == 0){
            dist[a[i]][b[i]] = c[i];
            dist[b[i]][a[i]] = c[i];
        }
    }
    rep(i,0,n) dist[i][i] = 0;
    rep(k,0,n)rep(i,0,n)rep(j,0,n) chmin(dist[i][j], dist[i][k] + dist[k][j]);
    rrep(i,q-1,0){
        auto [type, x, y] = query[i];
        if(type == 1){
            ll v = a[x], w = b[x], z = c[x];
            rep(j,0,n){
                rep(k,0,n){
                    chmin(dist[j][k], dist[j][v] + z + dist[w][k]);
                    chmin(dist[j][k], dist[j][w] + z + dist[v][k]);
                }
            }
        }else{
            ans[i] = (dist[x][y] == INF ? -1 : dist[x][y]);
        }
    }
    rep(i,0,q){
        if(get<0>(query[i]) == 2){
            cout << ans[i] << endl;
        }
    }
    return 0;
}