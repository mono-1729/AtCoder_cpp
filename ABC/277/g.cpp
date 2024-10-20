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
    vector<vector<ll>> g(n);
    rep(i,0,m){
        ll u, v; cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<ll> c(n);
    vector<mint> div(m+1, 1);
    rep(i,1,m+1) div[i] /= i;
    rep(i,0,n) cin >> c[i];
    mint ans = 0;
    vector dp(n,vector<mint>(3,0));
    dp[0][0] = 1;
    rep(_,0,k){
        vector ndp(n,vector<mint>(3,0));
        rep(i,0,n){
            ll l = g[i].size();
            mint x0 = dp[i][0]*div[l], x1 = dp[i][1]*div[l], x2 = dp[i][2]*div[l];
            for(auto j: g[i]){
                if(c[j]){
                    ans += x2;
                    ndp[j][0] += x0;
                    ndp[j][1] += x1;
                    ndp[j][2] += x2;
                }else{
                    ndp[j][0] += x0;
                    ndp[j][1] += x1 + x0*2;
                    ndp[j][2] += x2 + x1 + x0;
                }
            }
        }
        swap(dp, ndp);
    }
    cout << ans.val() << endl;
    return 0;
}