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
    ll n, d; cin >> n >> d;
    vector<ll> p(n), q(n);
    rep(i,0,n) cin >> p[i];
    rep(i,0,n) cin >> q[i];
    vector dp(n+1,vector<vector<mint>>(d+1,vector<mint>(d+1,0)));
    dp[0][0][0] = 1;
    rep(i,0,n){
        // 右上から左下
        vector<vector<mint>> sum1(d+d+1,vector<mint>(d+1,0));
        // 左上から左下
        vector<vector<mint>> sum2(d+d+1,vector<mint>(d+1,0));
        rep(j,0,d+1)rep(k,0,d+1){
            sum1[j+k][j] += dp[i][j][k];
            sum2[j-k+d][j] += dp[i][j][k];
        }
        rep(j,0,d+d+1)rep(k,0,d){
            sum1[j][k+1] += sum1[j][k];
            sum2[j][k+1] += sum2[j][k];
        }
        ll dist = abs(q[i]-p[i]);
        rep(j,0,d+1)rep(k,0,d+1){
            if(j+k>=dist){
                dp[i+1][j][k] += sum1[j+k-dist][j];
                if(j-dist>0) dp[i+1][j][k] -= sum1[j+k-dist][j-dist-1];
            }
            if(j-k+dist+d <= 2*d && j>0){
                dp[i+1][j][k] += sum2[j-k+dist+d][j-1];
            }
            if(j-dist-1 >= 0){
                dp[i+1][j][k] += sum2[j-k-dist+d][j-dist-1];
            }
        }
    }

    mint ans = 0;
    rep(i,0,d+1)rep(j,0,d+1) ans += dp[n][i][j];
    cout << ans.val() << endl;

    return 0;
}