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
    ll n, m; cin >> n >> m;
    vector<ll> a(n), b(n);
    rep(i,0,n) cin >> a[i];
    rep(i,0,n) cin >> b[i];
    vector<pll> vec(n);
    rep(i,0,n) vec[i] = {b[i],i};
    sort(vec.begin(), vec.end());
    vector<vector<pll>> g(n*2);
    rep(i,0,n){
        g[n+i].push_back({i,0});
        auto it = lower_bound(all(vec), make_pair(m-a[i], -INF));
        auto [num, id] = (it == vec.end()? *vec.begin(): *it);
        g[i].push_back({n+id, (num+a[i])%m});
    }
    rep(i,0,n-1){
        auto [num1, id1] = vec[i];
        auto [num2, id2] = vec[i+1];
        g[n+id1].push_back({n+id2, num2-num1});
    }
    {
        auto [num1, id1] = vec[n-1];
        auto [num2, id2] = vec[0];
        g[n+id1].push_back({n+id2, m+num2-num1});
    }
    

    priority_queue<pll, vector<pll>, greater<pll>> que;
    vector<ll> dist(2*n, (1LL<<60));
    que.push(make_pair(0, 0));
    dist[0] = 0;
    while(!que.empty()){
        pll q = que.top(); que.pop();
        ll d = q.first, u = q.second;
        if(dist[u] < d) continue;
        for(auto nq: g[u]){
            ll v = nq.first, cost = nq.second;
            if(dist[v] > d+cost){
                dist[v] = d+cost;
                que.push({dist[v], v});
            }
        }
    }
    cout << dist[n-1] << endl;
    return 0;
}