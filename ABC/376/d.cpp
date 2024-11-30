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
    vector<vector<ll>> g(n);
    unordered_map<ll, ll> mp;
    rep(i,0,m){
        ll a, b; cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        mp[a*n+b] = 1;
    }
    vector<ll> dist(n, INF);
    dist[0] = 0;
    queue<ll> q;
    q.push(0);
    while(!q.empty()){
        ll v = q.front(); q.pop();
        for(auto nv : g[v]){
            if(dist[nv] == INF){
                dist[nv] = dist[v] + 1;
                q.push(nv);
            }
        }
    }
    ll ans = INF;
    rep(i,1,n){
        if(mp[i*n] > 0) chmin(ans, dist[i]+1);
    }
    cout << (ans == INF ? -1 : ans) << endl;
    return 0;
}