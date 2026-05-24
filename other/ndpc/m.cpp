#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <stdlib.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define inr(l, x, r) (l <= x && x < r)
#define ll long long
#define ld long double
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
    if(b == 0) return a;
    if(a%b == 0){
      return b;
    }else{
      return gcd(b, a%b);
    }
}

ll lcm(ll a, ll b){
    return a*b / gcd(a, b);
}

ll powMod(ll x, ll n, ll mod) {
    if (n == 0) return 1 % mod;
    ll val = powMod(x, n / 2, mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}

int main() {
    ll n; cin >> n;
    ll m = 1LL<<n;
    string s; cin >> s;
    vector<ll> num(m);
    vector<mint> dp(m), pow10(m+1,1);
    rep(i,0,m) pow10[i+1] = pow10[i]*10;
    rep(i,0,m) dp[i] = s[i]-'0', num[i] = 1;
    rep(i,0,n)rep(j,0,m){
        if(j>>i&1) continue;
        ll x = j+(1<<i);
        dp[x] = dp[x]+dp[j]*pow10[num[x]];
        num[x] += num[j];
    }
    ll ans = 0;
    rep(i,0,m) ans += (dp[i].val())^i;
    cout << ans << endl;
    return 0;
}