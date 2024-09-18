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
    vector<ll> r(n), b(n), rs(1<<n), bs(1<<n);
    vector<mint> fac(m+1,1);
    rep(i,1,m+1) fac[i] = fac[i-1] * i;
    rep(i,0,m){
        ll id; cin >> id; id--;
        r[id]++;
    }
    rep(i,0,m){
        ll id; cin >> id; id--;
        b[id]++;
    }
    vector<mint> dp(1<<n,0), dp2(1<<n,0);
    rep(mask,0,1<<n){
        ll rsum = 0, bsum = 0;
        rep(i,0,n)if(mask >> i & 1){
            rsum += r[i];
            bsum += b[i];
        }
        rs[mask] = rsum; bs[mask] = bsum;
        if(rsum == bsum) dp[mask] = dp2[mask] = fac[rsum];
    }
    mint ans = 0;
    rep(mask,1,1<<n){
        for(ll t = (mask-1)&mask; t*2 > mask; t = (t-1) & mask){
            dp[mask] -= dp[t] * dp2[mask^t];
        }
        ans += dp[mask] * fac[m-rs[mask]];
    }
    cout << (ans/fac[m]).val() << endl;
    return 0;
}