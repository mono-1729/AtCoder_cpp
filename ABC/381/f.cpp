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
    vector<ll> a(n);
    vector<vector<ll>> idx(20);
    rep(i,0,n) cin >> a[i], a[i]--, idx[a[i]].push_back(i);
    vector<ll> dp(1<<20, INF);
    dp[0] = 0;
    rep(i,0,1<<20){
        if(dp[i] == INF) continue;
        rep(j,0,20) if(!(i>>j&1)){
            ll left = lower_bound(idx[j].begin(), idx[j].end(), dp[i]) - idx[j].begin();
            if(left+1 < idx[j].size()) chmin(dp[i|(1<<j)], idx[j][left+1]);
        }
    }
    ll ans = 0;
    rep(i,0,1<<20) if(dp[i] != INF)chmax(ans, __builtin_popcount(i)*2);
    cout << ans << endl;
    return 0;
}