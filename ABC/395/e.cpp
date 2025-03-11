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

int main() {
    ll n, m, x; cin >> n >> m >> x;
    vector<vector<pll>> g(n);
    rep(i,0,m){
        ll u, v; cin >> u >> v;
        u--;v--;
        g[u].push_back({v,0});
        g[v].push_back({u,1});
    }
    // sを始点とする各頂点への距離の最小値を格納した配列を返す
    priority_queue<tuple<ll,ll,ll>, vector<tuple<ll,ll,ll>>, greater<tuple<ll,ll,ll>>> que;
    vector<vector<ll>> dist(n,vector<ll>(2,INF));
    que.push({0,0,0});
    dist[0][0] = 0;
    while(!que.empty()){
        auto [d, u, f] = que.top(); que.pop();
        if(dist[u][f] < d) continue;
        for(auto nq: g[u]){
            ll v = nq.first, cost = nq.second;
            if(cost != f) continue;
            if(dist[v][f] > d+1){
                dist[v][f] = d+1;
                que.push({dist[v][f], v, f});
            }
        }
        if(dist[u][1-f] > d+x){
            dist[u][1-f] = d+x;
            que.push({dist[u][1-f], u, 1-f});
        }
    }
    cout << min(dist[n-1][0], dist[n-1][1]) << endl;

    return 0;
}