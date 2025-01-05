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
    ll l, r; cin >> l >> r;

    auto solve = [&](ll x){
        string s = to_string(x);
        ll n = s.size();
        vector<vector<vector<ll>>> dp(n+1, vector<vector<ll>>(10, vector<ll>(2, 0)));
        dp[0][0][0] = 1;
        rep(i, 0, n){
            rep(j, 0, 10){
                rep(d,0,10){
                    if(j == 0) dp[i+1][d][1] += dp[i][j][1];
                    else {
                        if(d < j) dp[i+1][j][1] += dp[i][j][1];
                    }
                }
                rep(d,0,s[i]-'0'){
                    if(j == 0) dp[i+1][d][1] += dp[i][j][0];
                    else {
                        if(d < j) dp[i+1][j][1] += dp[i][j][0];
                    }
                }
                if(j == 0) dp[i+1][s[i]-'0'][0] += dp[i][j][0];
                else {
                    if(s[i]-'0' < j) dp[i+1][j][0] += dp[i][j][0];
                }
            }
        }
        ll res = 0;
        rep(i, 0, 10){
            res += dp[n][i][0] + dp[n][i][1];
        }
        return res;
    };
    
    cout << solve(r) - solve(l-1) << endl;
    return 0;
}