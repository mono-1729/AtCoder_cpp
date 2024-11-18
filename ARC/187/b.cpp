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
    ll n, m; cin >> n >> m;
    vector<ll> b(n);
    rep(i, 0, n) cin >> b[i], b[i] = b[i] == -1 ? -1 : b[i]-1;
    vector<vector<mint>> dp(n+1, vector<mint>(m+1, 0));
    vector<ll> num(n+1,0);
    vector<ll> maxi(n+1,-1);
    rrep(i, n-1, 0){
        maxi[i] = max(maxi[i+1], b[i]);
        num[i] = num[i+1] + (b[i] == -1);
    }
    dp[0][m] = 1;
    mint ans = 0;
    rep(i, 0, n){
        vector<mint> sum(m+2, 0);
        rep(j, 0, m+1) sum[j+1] = sum[j] + dp[i][j];
        rep(j, 0, m){
            if(b[i] == -1){
                dp[i+1][j] = dp[i][j]*(m-j) + sum[m+1] - sum[j+1];
                if(maxi[i+1] < j){
                    ans += dp[i+1][j] * powMod(j, num[i+1]);
                }
            }else{
                if(j == b[i]){
                    dp[i+1][j] = sum[m+1] - sum[j];
                }else if(j < b[i]){
                    dp[i+1][j] = dp[i][j];
                }
                if(maxi[i+1] < j){
                    ans += dp[i+1][j] * powMod(j, num[i+1]);
                }
            }
        }
    }
    cout << ans.val() << endl;
    return 0;
}