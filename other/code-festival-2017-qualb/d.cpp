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
    string s; cin >> s;
    vector<pll> vec;
    ll idx = 0;
    while(idx < n){
        char x = s[idx];
        ll l = idx;
        while(idx < n && s[idx] == s[l]) idx++;
        vec.push_back({x-'0', idx-l});
    }
    ll m = vec.size();
    vector<vector<ll>> dp(m+1, vector<ll>(16,-INF));
    dp[0][15] = 0;
    rep(i,0,m)rep(j,0,16){
        if(dp[i][j] == -INF) continue;
        ll l1 = j/4, l2 = j%4;
        chmax(dp[i+1][j/4], dp[i][j]);
        if(vec[i].first == 0 || l1 != 0 || vec[i-1].second != 1) continue;
        if(l2 == 0){
            chmax(dp[i+1][15], dp[i][j] + vec[i].second);
            chmax(dp[i+1][7], dp[i][j] + vec[i-2].second);
            if(vec[i].second > 1) chmax(dp[i+1][11], dp[i][j] + vec[i].second-1);
        }
        if(l2 == 1 && vec[i-2].second > 1){
            chmax(dp[i+1][15], dp[i][j] + vec[i].second);
            chmax(dp[i+1][7], dp[i][j] + vec[i-2].second-1);
            if(vec[i].second > 1) chmax(dp[i+1][11], dp[i][j] + vec[i].second-1);
        }
        if(l2 == 2 && vec[i-2].second > 1){
            chmax(dp[i+1][15], dp[i][j] + vec[i].second);
            chmax(dp[i+1][7], dp[i][j] + 1);
            if(vec[i].second > 1) chmax(dp[i+1][11], dp[i][j] + vec[i].second-1);
        }
    }
    ll ans = 0;
    rep(i,0,16) chmax(ans, dp[m][i]);
    cout << ans << endl;
    return 0;
}