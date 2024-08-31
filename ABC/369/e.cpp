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
    ll n, m; cin >> n >> m;
    vector<vector<pll>> g(n);
    vector<vector<ll>> dist(n, vector<ll>(n, INF));
    vector<ll> u(m), v(m), t(m);
    rep(i,0,n) dist[i][i] = 0;
    rep(i,0,m){
        ll a, b, c; cin >> a >> b >> c;
        a--; b--;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
        chmin(dist[a][b], c);
        chmin(dist[b][a], c);
        u[i] = a;
        v[i] = b;
        t[i] = c;
    }
    rep(k,0,n)rep(i,0,n)rep(j,0,n) chmin(dist[i][j], dist[i][k] + dist[k][j]);
    ll q; cin >> q;
    rep(i,0,q){
        ll k; cin >> k;
        vector<ll> b(k);
        rep(j,0,k) cin >> b[j], b[j]--;
        vector<vector<ll>> dp(n, vector<ll>(1<<k, INF));
        dp[0][0] = 0;
        rep(mask,0,1<<k)rep(i,0,n){
            if(dp[i][mask] == INF) continue;
            rep(bit,0,k){
                if(mask>>bit&1) continue;
                chmin(dp[u[b[bit]]][mask|(1<<bit)], dp[i][mask] + dist[i][v[b[bit]]] + t[b[bit]]);
                chmin(dp[v[b[bit]]][mask|(1<<bit)], dp[i][mask] + dist[i][u[b[bit]]] + t[b[bit]]);
            }
        }
        ll ans = INF;
        rep(i,0,n) chmin(ans, dp[i][(1<<k)-1] + dist[i][n-1]);
        cout << ans << endl;
    }
    
    return 0;
}