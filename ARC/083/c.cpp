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
    vector<vector<ll>> g(n);
    vector<ll> x(n);
    rep(i,1,n){
        ll p; cin >> p;
        p--;
        g[i].push_back(p);
        g[p].push_back(i);
    }
    rep(i,0,n) cin >> x[i];

    auto solve = [&](auto solve, ll v, ll p) -> int {
        vector<ll> dp(x[v]+1,0);
        dp[0] = 1;
        ll sum = 0;
        for(auto nv: g[v]){
            if(nv == p) continue;
            ll num = solve(solve, nv, v);
            if(num == -1) return -1;
            vector<ll> ndp(x[v]+1, 0);
            rep(i,0,x[v]+1){
                if(dp[i] == 0) continue;
                if(i+x[nv] <= x[v]) ndp[i+x[nv]] = 1;
                if(i+num <= x[v]) ndp[i+num] = 1;
            }
            sum += x[nv]+num;
            swap(ndp,dp);
        }
        ll maxn = -1;
        rep(i,0,x[v]+1){
            if(dp[i]) maxn = i;
        }
        if(maxn == -1) return -1;
        else return sum - maxn;
    };

    if(solve(solve,0,-1) == -1) cout << "IMPOSSIBLE" << endl;
    else cout << "POSSIBLE" << endl;

    return 0;
}