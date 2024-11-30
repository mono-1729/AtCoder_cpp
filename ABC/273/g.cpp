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

ll maxnum=5005;
vector<ll> fac(maxnum), inv(maxnum), finv(maxnum);
void init_fac(){
    fac[0] = fac[1] = 1;
    inv[1] = 1;
    finv[0] = finv[1] = 1;
    rep(i, 2, maxnum){
        fac[i] = fac[i-1]*i%MOD;
        inv[i] = MOD-MOD/i*inv[MOD%i]%MOD;
        finv[i] = finv[i-1]*inv[i]%MOD;
    }
}
ll nCr(ll n, ll r){
    if(n < 0 or n-r < 0 or r < 0) return 0;
    return fac[n]*(finv[n-r]*finv[r]%MOD)%MOD;
}
ll nHr(ll n, ll r){
    return nCr(n+r-1, r);
}

int main() {
    init_fac();
    ll n; cin >> n;
    ll rsum = 0, csum = 0;
    ll c1 = 0 , c2 = 0;
    vector<ll> r(n), c(n);
    rep(i,0,n) cin >> r[i], rsum += r[i];
    rep(i,0,n){
        cin >> c[i];
        csum += c[i];
        if(c[i] == 1) c1++;
        else if(c[i] == 2) c2++;
    }
    if(rsum != csum){
        cout << 0 << endl;
        return 0;
    }
    vector<vector<mint>> dp(n+1, vector<mint>(c2+1, 0));
    dp[0][c2] = 1;
    rep(i,0,n){
        rep(j,0,c2+1){
            if(r[i] == 0) dp[i+1][j] += dp[i][j];
            if(r[i] == 1){
                if(j > 0) dp[i+1][j-1] += dp[i][j] * j;
                if(j*2 + 1 <= rsum) dp[i+1][j] += dp[i][j] * (rsum - j*2);
            }
            if(r[i] == 2){
                if(j > 1) dp[i+1][j-2] += dp[i][j] * nCr(j, 2);
                if(j > 0) dp[i+1][j-1] += dp[i][j] * j * (rsum - j*2 + 1);
                if(j*2 + 2 <= rsum) dp[i+1][j] += dp[i][j] * nCr(rsum - j*2, 2);
            }
        }
        rsum -= r[i];
    }

    cout << dp[n][0].val() << endl;
    return 0;
}