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
constexpr ll MOD = 1000000007;
// constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint1000000007;

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
    ll s, t; cin >> s >> t;
    s--; t--;
    vector<vector<pll>> g(n);
    rep(i,0,m){
        ll u, v, d; cin >> u >> v >> d;
        u--;v--;
        g[u].push_back({v,d});
        g[v].push_back({u,d});
    }
    ll min_dist;
    mint ans = 0;
    // sを始点とする各頂点への距離の最小値を格納した配列を返す
    priority_queue<pll, vector<pll>, greater<pll>> que;
    vector<pair<ll,mint>> dist1(n, {1LL<<60,0});
    que.push(make_pair(0, s));
    dist1[s] = {0,1};
    while(!que.empty()){
        pll q = que.top(); que.pop();
        ll d = q.first, u = q.second;
        if(dist1[u].first < d) continue;
        for(auto nq: g[u]){
            ll v = nq.first, cost = nq.second;
            if(dist1[v].first > d+cost){
                dist1[v] = {d+cost,dist1[u].second};
                que.push({dist1[v].first, v});
            }
            else if (dist1[v].first == d+cost){
                dist1[v].second += dist1[u].second;
            }
        }
    }
    min_dist = dist1[t].first;
    vector<mint> num(n+m,0);
    {
        // sを始点とする各頂点への距離の最小値を格納した配列を返す
        priority_queue<pll, vector<pll>, greater<pll>> que;
        vector<pair<ll,mint>> dist(n, {1LL<<60,0});
        que.push(make_pair(0, t));
        dist[t] = {0,1};
        while(!que.empty()){
            pll q = que.top(); que.pop();
            ll d = q.first, u = q.second;
            if(dist[u].first < d) continue;
            if(d + dist1[u].first == min_dist && d*2 == min_dist){
                ans += (dist1[u].second * dist[u].second) * (dist1[t].second - dist[u].second * dist1[u].second);
            }
            for(auto nq: g[u]){
                ll v = nq.first, cost = nq.second;
                if(d*2 < min_dist && (d+cost)*2 > min_dist && d+cost+dist1[v].first == min_dist){
                    // cout << "2 " << u << " " << v << endl;
                    ans += (dist1[v].second * dist[u].second) * (dist1[t].second - dist[u].second * dist1[v].second);
                }
                if(dist[v].first > d+cost){
                    dist[v] = {d+cost,dist[u].second};
                    que.push({dist[v].first, v});
                }
                else if (dist[v].first == d+cost){
                    dist[v].second += dist[u].second;
                }
            }
        }
    }
    cout << ans.val() << endl;
    return 0;
}