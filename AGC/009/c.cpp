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
    ll n, a, b; cin >> n >> a >> b;
    vector<ll> s(n+1, -INF);
    rep(i,1,n+1) cin >> s[i];
    vector<ll> cnta(n+1,0), cntb(n+1,0);
    rep(i,1,n+1){
        cnta[i] += cnta[i-1];
        cntb[i] += cntb[i-1];
        if(s[i]-s[i-1] < a) cnta[i]++;
        if(s[i]-s[i-1] < b) cntb[i]++;
    }
    vector<vector<mint>> dp(n+2,vector<mint>(2,0));
    dp[0][0] = dp[0][1] = 1;
    dp[1][0] = dp[1][1] = -1;
    rep(i,0,n){
        if(i > 0){
            dp[i][0] += dp[i-1][0];
            dp[i][1] += dp[i-1][1];
        }
        ll l, r;
        {
            l = lower_bound(s.begin(), s.end(), s[i]+b) - s.begin() - 1;
            chmax(l,i+1);
            r = upper_bound(cnta.begin(), cnta.end(), cnta[i+1]) - cnta.begin();
            // cout << "0 " << l << " " << r << endl;
            if(l < r){
                dp[l][1] += dp[i][0];
                dp[r][1] -= dp[i][0];
            }
        }
        {
            l = lower_bound(s.begin(), s.end(), s[i]+a) - s.begin() - 1;
            r = upper_bound(cntb.begin(), cntb.end(), cntb[i+1]) - cntb.begin();
            chmax(l,i+1);
            // cout << "1 " << l << " " << r << endl;
            if(l < r){
                dp[l][0] += dp[i][1];
                dp[r][0] -= dp[i][1];
            }
        }
    }
    mint ans = 0;
    rep(i,0,n){
        if(cnta[i+1] == cnta[n]) ans += dp[i][0];
        if(cntb[i+1] == cntb[n]) ans += dp[i][1];
    }
    cout << ans.val() << endl;
    return 0;
}