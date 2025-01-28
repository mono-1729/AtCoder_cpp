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
    ll n, t; cin >> n >> t;
    vector<pll> ab(n);
    rep(i,0,n) cin >> ab[i].first >> ab[i].second;
    sort(ab.begin(), ab.end(), [](const auto x, const auto y) -> bool {
        if(x.first == 0 && y.first == 0) return x.second < y.second;
        return (x.second+1)*y.first < (y.second+1)*x.first;  
    });
    ll l0 = n;
    rrep(i,n-1,0) if(ab[i].first == 0) l0 = i;
    vector<vector<ll>> dp(l0+1,vector<ll>(31,IINF));
    dp[0][0] = 0;
    rep(i,0,l0){
        auto [a, b] = ab[i];
        rep(j,0,30){
            if(dp[i][j] == IINF) continue;
            chmin(dp[i+1][j], dp[i][j]);
            chmin(dp[i+1][j+1], dp[i][j]+1 + (dp[i][j]+1)*a+b);
        }
    }
    vector<ll> time(n-l0+1, 0);
    rep(i,0,n-l0) time[i+1] = time[i] + 1 + ab[l0+i].second;
    ll ans = 0;
    rep(i,0,30){
        if(dp[l0][i] == IINF) continue;
        ll num = 0;
        rep(j,0,n-l0+1) if(t - time[j] >= dp[l0][i]) num = i+j;
        chmax(ans,num);
    }
    cout << ans << endl;
    return 0;
}