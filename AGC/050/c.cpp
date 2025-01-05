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
    mint ans = 1;
    vector<ll> bid = {-IINF};
    rep(i,0,n){
        if(s[i] == '?') ans *= 2;
        if(s[i] == 'B') bid.push_back(i);
    }
    vector<vector<mint>> dp(n+1,vector<mint>(22));
    dp[n][0] = 1;
    rrep(i,n,1){
        if(bid.back() == i-1) bid.pop_back();
        rep(j,0,21){
            if(s[i-1] != 'S' && bid.back() < i-1-(1<<j)) dp[max(0LL,i-1-(1<<j))][j+1] += dp[i][j];
            if(s[i-1] != 'B') dp[i-1][j] += dp[i][j];
        }
    }
    rep(i,0,22) ans -= dp[0][i];
    cout << ans.val() << endl;
    return 0;
}