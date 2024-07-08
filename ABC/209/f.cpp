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
    int n; cin >> n;
    vector<ll> h(n,0);
    rep(i,0,n) cin >> h[i];
    vector<vector<mint>> dp(n,vector<mint>(n,0));
    dp[0][0] = 1;
    rep(i,0,n-1){
        if(h[i] > h[i+1]){
            vector<mint> sum(n+1,0);
            rrep(j,n-1,0)sum[j] = sum[j+1] + dp[i][j];
            rep(j,0,i+2) dp[i+1][j] = sum[j];
            
        }else if(h[i] < h[i+1]){
            vector<mint> sum(n+1,0);
            rep(j,0,n)sum[j+1] = sum[j] + dp[i][j];
            rep(j,0,i+2) dp[i+1][j] = sum[j];
        }else{
            mint sum = 0;
            rep(j,0,n) sum += dp[i][j];
            rep(j,0,i+2) dp[i+1][j] = sum;
        }
    }
    mint ans = 0;
    rep(i,0,n) ans += dp[n-1][i];
    cout << ans.val() << endl;

    // rep(i,0,n+1){
    //     rep(j,0,n+1) cout << dp[i][j].val() << " ";
    //     cout << endl;
    // }
    return 0;
}