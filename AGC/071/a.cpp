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
#define all(x) (x).begin(), (x).end()
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
    rep(i,0,n) cin >> a[i];
    vector<vector<ll>> dp(n+1, vector<ll>(n+1, INF));
    vector<vector<vector<ll>>> dp2(n+1,vector<vector<ll>>(n+1,vector<ll>(3,INF)));
    vector<vector<ll>>ax(n+1, vector<ll>(n+1, 0));
    rep(i,0,n)rep(j,i,n) ax[i][j+1] = ax[i][j]^a[j];
    rep(i,0,n+1){
        dp[i][i] = 0;
        dp2[i][i][0] = 0;
    }
    rrep(i,n-1,0)rep(j,i+1,n+1){
        if((j-i)%2 == 1){
            rep(k,i,j){
                if((k-i)%2 == 0) chmin(dp2[i][j][1], dp2[i][k][0]+dp2[k+1][j][0]);
            }
            continue;
        }
        for(ll k = i+2; k < j; k += 2) chmin(dp[i][j], dp[i][k]+dp[k][j]);
        rep(k,i,j){
            if((k-i)%2 == 0) chmin(dp2[i][j][2], dp2[i][k][0]+dp2[k+1][j][1]);
        }
        chmin(dp[i][j], dp2[i][j][2]+ax[i][j]*2);
        dp2[i][j][0] = dp[i][j];
    }
    if(n%2 == 1){
        rep(i,0,n) chmin(dp[0][n], dp[0][i]+dp[i+1][n]+ax[0][n]);
    }
    cout << dp[0][n] << endl;
    return 0;
}