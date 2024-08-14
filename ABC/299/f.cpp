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
    string s; cin >> s;
    ll n = s.size();
    vector<vector<ll>> next(n+1, vector<ll>(26,INF));
    rep(i,0,n+1)rep(j,i+1,n){
        chmin(next[i][s[j]-'a'], j);
    }
    mint ans = 0;
    rep(right,1,n){
        ll left = s[0] == s[right] ? 0 : next[0][s[right]-'a'];
        if(left >= right) continue;
        vector<vector<mint>> dp(n,vector<mint>(n,0));
        dp[left][right] = 1;
        rep(i,0,n)rep(j,i+1,n){
            if(next[i][s[right] -'a'] == right) ans += dp[i][j];
            rep(ss,0,26){
                ll ni = next[i][ss], nj = next[j][ss];
                if(ni >= right || nj == INF) continue;
                dp[ni][nj] += dp[i][j];
            }
        }
    }
    cout << ans.val() << endl;
    return 0;
}