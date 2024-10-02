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

mint dp[41][1<<5][1<<7][1<<5];

int main() {
    ll n, x, y, z; cin >> n >> x >> y >> z;
    mint ans = 0;
    vector<mint> pow10(n+1,1);
    rep(i,1,n+1) pow10[i] = pow10[i-1] * 10;
    dp[0][1][0][0] = 1;
    ll fx = (1 << x) -1, fy = (1 << y) -1, fz = (1 << z) -1;
    rep(i,0,n)rep(j,0,1<<x)rep(k,0,1<<y)rep(l,0,1<<z){
        if(dp[i][j][k][l] == 0) continue;
        rep(next,1,11){
            if(next <= z && (l>>(z-next) & 1)){
                ans += dp[i][j][k][l] * pow10[n-i-1];
                continue;
            }
            ll nj = 1 | ((j << next)&fx);
            ll nk = ((next <= x && (j>>(x-next) & 1))? 1 : 0) | ((k << next)&fy);
            ll nl = ((next <= y && (k>>(y-next) & 1))? 1 : 0) | ((l << next)&fz);
            dp[i+1][nj][nk][nl] += dp[i][j][k][l];
        }
    }

    cout << ans.val() << endl;
    return 0;
}