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
    ll n, m, k; cin >> n >> m >> k;
    vector<vector<pll>> g(n);
    rep(i, 0, m){
        ll a, b, c; cin >> a >> b >> c;
        a--; b--;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    // sを始点とする各頂点への距離の最小値を格納した配列を返す
    vector<vector<ll>> dist(n, vector<ll>(n, INF));
    rep(s,0,n){
        priority_queue<pll, vector<pll>, greater<pll>> que;
        que.push(make_pair(0, s));
        dist[s][s] = 0;
        while(!que.empty()){
            pll q = que.top(); que.pop();
            ll d = q.first, u = q.second;
            if(dist[s][u] < d) continue;
            for(auto nq: g[u]){
                ll v = nq.first, cost = nq.second;
                if(dist[s][v] > d+cost){
                    dist[s][v] = d+cost;
                    que.push({dist[s][v], v});
                }
            }
        }
    }
    vector<ll> dp(k+1, -INF);
    dp[0] = 0;
    vector<pll> ct(k+1);
    ct[0] = {0, 0};
    rep(i,1,k+1){
        ll c, t; cin >> c >> t;
        c--;
        ct[i] = {t,c};
    }
    sort(ct.begin(), ct.end());
    vector<ll> c(k+1), t(k+1);
    rep(i,0,k+1){
        t[i] = ct[i].first;
        c[i] = ct[i].second;
    }
    rep(i,0,k){
        rep(j,i+1,k+1){
            if(t[j] - t[i] < dist[c[i]][c[j]]) continue;
            chmax(dp[j], dp[i] + 1);
        }
    }
    ll ans = 0;
    rep(i,0,k+1) chmax(ans, dp[i]);
    cout << ans << endl;
    return 0;
}