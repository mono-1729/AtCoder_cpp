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
// constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint1000000007;


int main() {
    ll l, r; cin >> l >> r;
    vector<vector<vector<mint>>> dp(61,vector<vector<mint>>(2,vector<mint>(2,0)));
    rrep(i,59,0){
        ll x = ((r>>i) & 1), y = ((l>>i) & 1);
        if((1LL << i <= r) && (1LL << (i+1) > l)){
            ll j = ((1LL << (i+1))-1) <= r ? 1 : 0;
            ll k = (1LL << i) >= l ? 1 : 0;
            dp[i][j][k] += 1;
        }
        dp[i][1][1] += dp[i+1][1][1]*3;
        if(y) dp[i][1][0] += dp[i+1][1][0];
        else{
            dp[i][1][1] += dp[i+1][1][0];
            dp[i][1][0] += dp[i+1][1][0]*2;
        }
        if(x){
            dp[i][1][1] += dp[i+1][0][1];
            dp[i][0][1] += dp[i+1][0][1]*2;
        }else dp[i][0][1] += dp[i+1][0][1];
        if(x > y){
            dp[i][1][0] += dp[i+1][0][0];
            dp[i][0][1] += dp[i+1][0][0];
            dp[i][0][0] += dp[i+1][0][0];
        }else if(x == y) dp[i][0][0] += dp[i+1][0][0];
    }
    mint ans = dp[0][0][0] + dp[0][1][0] + dp[0][0][1] + dp[0][1][1];
    cout << ans.val() << endl;
    return 0;
}