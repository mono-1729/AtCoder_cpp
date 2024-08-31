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
    ll n; cin >> n;
    vector<ll> u(n-1), v(n-1), w(n-1);
    vector<vector<pll>> g(n);
    rep(i,0,n-1){
        cin >> u[i] >> v[i] >> w[i];
        u[i]--; v[i]--;
        g[u[i]].push_back({v[i], w[i]});
        g[v[i]].push_back({u[i], w[i]});
    }
    vector<ll> dist(n, 0);
    auto dfs = [&](auto dfs, ll now, ll par, ll edge) -> pll {
        ll ma = 0;
        ll idx = now;
        for(auto [to, cost] : g[now]){
            if(to == par) continue;
            pll res = dfs(dfs, to, now, cost);
            if(res.first > ma){
                ma = res.first;
                idx = res.second;
            }
        }
        dist[idx] += edge;
        return {ma + edge, idx};
    };
    dfs(dfs, 0, -1, 0);
    sort(dist.begin(), dist.end(), greater<ll>());
    ll ans = 0;
    rep(i,0,n){
        ans += dist[i]*2;
        cout << ans << endl;
    }
    return 0;
}