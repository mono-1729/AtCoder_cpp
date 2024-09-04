#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <atcoder/all>
using namespace atcoder;
using namespace boost::multiprecision;
using namespace std;
#define rep(i, a, n) for(int i = a; i < n; i++)
#define rrep(i, a, n) for(int i = a; i >= n; i--)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
//constexpr ll MOD = 1000000007;
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint;

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
    int n, k, p; cin >> n >> k >> p;
    mint::set_mod(p);
    vector dp(n,vector<vector<vector<mint>>>(k+1,vector<vector<mint>>(n,vector<mint>(n,0))));
    dp[0][0][0][0] = 1;
    auto calcsum = [&](int i, int j, int xl, int xr, int yl, int yr) -> mint {
        if(xl > xr || yl > yr) return 0;
        mint res = dp[i][j][xr][yr];
        if(xl > 0) res -= dp[i][j][xl-1][yr];
        if(yl > 0) res -= dp[i][j][xr][yl-1];
        if(xl > 0 && yl > 0) res += dp[i][j][xl-1][yl-1];
        return res;
    };
    rep(i,1,n){
        rep(j,0,min(i+1,k+1)){
            rep(x,0,i+1)rep(y,0,i+1){
                dp[i][j][x][y] += dp[i-1][j][i-1][i-1] - calcsum(i-1,j,x,i-1,y,i-1) - calcsum(i-1,j,0,x-1,0,y-1);
                if(j > 0){
                    dp[i][j][x][y] += calcsum(i-1,j-1,x,i-1,y,i-1) + calcsum(i-1,j-1,0,x-1,0,y-1);
                }
            }
        }
        rep(j,0,min(i+1,k+1))rep(x,0,i)rep(y,0,i+1) dp[i][j][x+1][y] += dp[i][j][x][y];
        rep(j,0,min(i+1,k+1))rep(x,0,i+1)rep(y,0,i) dp[i][j][x][y+1] += dp[i][j][x][y];
    }
    cout << dp[n-1][k][n-1][n-1].val() << endl;
    return 0;
}