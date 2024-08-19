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
//constexpr ll MOD = 998244353;
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
    ll n; cin >> n;
    vector<vector<ll>> g(n);
    rep(i,0,n-1){
        ll u, v; cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    auto solve = [&](auto& solve, ll v, ll p) -> vector<vector<mint>> {
        vector<vector<mint>> dp = {{1,0,0},{0,0,1}};
        for(auto nv: g[v]){
            if(nv == p) continue;
            vector cdp = solve(solve, nv, v);
            ll m1 = dp.size(), m2 = cdp.size();
            vector ndp(m1+m2-1, vector<mint>(3,0));
            rep(i,0,m1)rep(j,0,m2){
                ndp[i+j][0] += dp[i][0]*(cdp[j][0]+cdp[j][1]);
                ndp[i+j][1] += dp[i][1]*(cdp[j][0]+cdp[j][1]+cdp[j][2]);
                if(i+j+1 < ndp.size()){
                    ndp[i+j+1][1] += dp[i][0]*cdp[j][2];
                    ndp[i+j+1][2] += dp[i][2]*cdp[j][0];
                }
                ndp[i+j][2] += dp[i][2]*(cdp[j][1]+cdp[j][2]);
            }
            swap(ndp,dp);
        } 
        return dp;
    };
    vector<vector<mint>> dp = solve(solve, 0, -1);
    rep(i,0,n+1) cout << (dp[i][0]+dp[i][1]+dp[i][2]).val() << endl;
    return 0;
}