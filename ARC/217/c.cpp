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

ll maxnum=200005;
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

void solve(){
    init_fac();
    ll n, c; cin >> n >> c;
    vector<ll> a(n+1);
    rep(i,1,n+1) cin >> a[i];
    a[0] = 1;
    sort(all(a));
    vector<mint> ans(n+1);
    rep(i,0,n+1){
        vector<mint> dp(n+1);
        dp[n] = 1;
        rep(j,0,i){
            vector<mint> ndp(n+1);
            vector<mint> ok(n+1), ng(n+1);
            ok[0] = ng[0] = 1;
            ng[1] = (mint)(a[j+1]-a[j])/(c-a[j]+1);
            ok[1] = 1-ng[1];
            rep(k,1,n){
                ok[k+1] = ok[k]*ok[1];
                ng[k+1] = ng[k]*ng[1];
            }
            rep(k,i-j,n+1)rep(l,i-j,k+1){
                ndp[l] += ok[l]*ng[k-l]*dp[k]*nCr(k,l);
            }
            // if(i == 2){
            //     for(auto x: ndp) cout << x.val() << " ";
            //     cout << endl;
            // }
            swap(dp,ndp);
        }
        for(auto x: dp) ans[i] += x;
    }
    rep(i,0,n) ans[i] -= ans[i+1];
    for(auto x : ans) cout << x.val() << " ";
    cout << endl;
}

int main() {
    ll t; cin >> t;
    while(t--){
        solve();
    }
    return 0;
}