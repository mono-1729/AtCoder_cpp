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
    vector<ll> a(n), pow10(10,1);
    rep(i,1,10) pow10[i] = pow10[i-1]*10;
    rep(i,0,n) cin >> a[i];
    vector<pll> dp(n+1,{INF,-1});
    dp[0] = {0,0};
    rep(i,0,9){
        vector<ll> vec(n);
        ll dsum = 0;
        rep(j,0,n) vec[j] = a[j]%pow10[i+1], dsum += vec[j]/pow10[i], vec[j] = pow10[i+1]-vec[j];
        sort(all(vec));
        vector<pll> ndp(n+1,{INF,-1});
        rep(j,0,n+1){
            auto [cnt, plus] = dp[j];
            if(cnt == INF) continue;
            rep(k,0,10){
                ll np = plus + pow10[i]*k;
                ll nid = upper_bound(all(vec),np)-vec.begin();
                ll nc = cnt+n*k-nid*9+dsum;
                if(ndp[nid].first > nc) ndp[nid] = {nc,np};
            }
        }
        swap(dp,ndp);
    }
    ll ans = INF;
    rep(i,0,n+1) chmin(ans,dp[i].first);
    // rep(i,0,n+1) cout << dp[i].first << " " << dp[i].second << endl;
    cout << ans << endl;
    return 0;
}