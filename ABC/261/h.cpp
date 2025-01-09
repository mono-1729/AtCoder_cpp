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
    ll n, m, s; cin >> n >> m >> s;
    s--;
    vector<vector<pll>> g(n);
    vector<vector<pll>> revg(n);
    vector<ll> outcnt(n);
    rep(i,0,m){
        ll a, b, c; cin >> a >> b >> c;
        a--;b--;
        g[a].push_back({b,c});
        revg[b].push_back({a,c});
        outcnt[a]++;
    }
    priority_queue<tuple<ll,ll,ll>, vector<tuple<ll,ll,ll>>,greater<tuple<ll,ll,ll>>> q;
    rep(i,0,n){
        if(outcnt[i] == 0){
            q.push({0,i,0});
            q.push({0,i,1});
        }
    }
    vector<vector<ll>> dp(n,vector<ll>(2,INF));
    while(!q.empty()){
        auto [cc, v, type] = q.top();q.pop();
        if(dp[v][type] < cc) continue;
        if(type == 0){
            dp[v][0] = cc;
            for(auto [x,c]: revg[v]){
                outcnt[x]--;
                if(outcnt[x] == 0){
                    ll num = 0;
                    for(auto [nv,cost]: g[x]) chmax(num, dp[nv][0] + cost);
                    q.push({num,x,1});
                }
            }
        }else{
            ll num = 0;
            for(auto [x,cost]: g[v]) chmax(num, dp[x][0] + cost);
            dp[v][1] = num;
            for(auto [x,c]: revg[v]){
                if(dp[x][0] > num+c) q.push({num+c,x,0});
            }
        }
    }

    if(dp[s][0] == INF) cout << "INFINITY" << endl;
    else cout << dp[s][0] << endl;
    return 0;
}