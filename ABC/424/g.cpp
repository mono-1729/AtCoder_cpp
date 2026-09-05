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
    ll n, m; cin >> n >> m;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    sort(all(a),greater<ll>());
    vector<ll> limit(m+2);
    rep(i,0,n){
        limit[1]++;
        limit[a[i]+1]--;
    }
    rep(i,0,m) limit[i+1] += limit[i];
    rep(i,0,m) limit[i+1] += limit[i];
    ll all = limit[m];
    vector<pll> bc(m);
    rep(i,0,m){
        ll b, c; cin >> b >> c;
        bc[i] = {b,c};
    }
    sort(all(bc),greater<pll>());
    vector<vector<ll>> dp(1,vector<ll>(all+1,-INF));
    dp[0][0] = 0;
    rep(i,0,m){
        auto [b,c] = bc[i];
        vector<vector<ll>> ndp(i+2,vector<ll>(all+1,-INF));
        rep(j,0,i+1)rep(k,0,all+1){
            if(dp[j][k] == -INF) continue;
            chmax(ndp[j][k], dp[j][k]);
            if(k+b <= limit[j+1]) chmax(ndp[j+1][k+b], dp[j][k]+c);
        }
        swap(dp,ndp);
    }
    ll ans = 0;
    // for(auto x: limit) cout << x << " ";
    // cout << endl;
    rep(i,1,m+1)rep(j,0,limit[i]+1){
        // cout << i << " " << dp[i].size() << " " << j << " " << all << endl;
        chmax(ans,dp[i][j]);
    }
    cout << ans << endl;
    return 0;
}