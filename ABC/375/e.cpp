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
    vector<ll> a(n), b(n);
    ll sum = 0;
    rep(i,0,n) cin >> a[i] >> b[i], a[i]--, sum += b[i];
    if(sum % 3 != 0){
        cout << -1 << endl;
        return 0;
    }
    vector<vector<vector<ll>>> dp(n+1, vector<vector<ll>>(sum/3 + 1, vector<ll>(sum/3 + 1, INF)));
    dp[0][0][0] = 0;
    rep(i,0,n){
        rep(j,0,sum/3+1){
            rep(k,0,sum/3+1){
                if(a[i] == 0){
                    if(j+b[i] <= sum/3) chmin(dp[i+1][j+b[i]][k], dp[i][j][k]);
                    if(k+b[i] <= sum/3) chmin(dp[i+1][j][k+b[i]], dp[i][j][k]+1);
                    chmin(dp[i+1][j][k], dp[i][j][k]+1);
                }
                if(a[i] == 1){
                    if(j+b[i] <= sum/3) chmin(dp[i+1][j+b[i]][k], dp[i][j][k]+1);
                    if(k+b[i] <= sum/3) chmin(dp[i+1][j][k+b[i]], dp[i][j][k]);
                    chmin(dp[i+1][j][k], dp[i][j][k]+1);
                }
                if(a[i] == 2){
                    if(j+b[i] <= sum/3) chmin(dp[i+1][j+b[i]][k], dp[i][j][k]+1);
                    if(k+b[i] <= sum/3) chmin(dp[i+1][j][k+b[i]], dp[i][j][k]+1);
                    chmin(dp[i+1][j][k], dp[i][j][k]);
                }
            }
        }
    }
    if(dp[n][sum/3][sum/3] == INF){
        cout << -1 << endl;
    }else{
        cout << dp[n][sum/3][sum/3] << endl;
    }
    return 0;
}