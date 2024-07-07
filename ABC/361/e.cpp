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
    vector<vector<pll>> g(n);
    ll ans = 0;
    rep(i, 0, n-1){
        ll a,b,c; cin >> a >> b >> c;
        a--; b--;
        g[a].push_back({b,c});
        g[b].push_back({a,c});
        ans += 2*c;
    }
    vector<ll> dist(n, INF);
    dist[0] = 0;
    queue<ll> q;
    q.push(0);
    while(!q.empty()){
        ll now = q.front();
        q.pop();
        for(auto [to, cost] : g[now]){
            if(dist[to] == INF){
                dist[to] = dist[now] + cost;
                q.push(to);
            }
        }
    }
    ll ans1 = 0;
    rep(i, 0, n){
        if(dist[i] > dist[ans1]){
            ans1 = i;
        }
    }
    dist.assign(n, INF);
    dist[ans1] = 0;
    q.push(ans1);
    while(!q.empty()){
        ll now = q.front();
        q.pop();
        for(auto [to, cost] : g[now]){
            if(dist[to] == INF){
                dist[to] = dist[now] + cost;
                q.push(to);
            }
        }
    }
    ll ans2 = 0;
    rep(i, 0, n){
        if(dist[i] > dist[ans2]){
            ans2 = i;
        }
    }
    cout << ans - dist[ans2] << endl;
    return 0;
}