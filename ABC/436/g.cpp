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
    a.push_back(1);
    n++;
    vector<mint> dp(1);
    dp[0] = 1;
    rep(i,0,60){
        rep(j,0,n){
            vector<mint> ndp(dp.size()+a[j]);
            rep(k,0,dp.size()){
                ndp[k] += dp[k];
                ndp[k+a[j]] += dp[k];
            }
            swap(dp,ndp);
        }
        vector<mint> ndp;
        ll x = (m>>i&1) ? 0 : 1;
        rep(j,0,((ll)dp.size()+x)/2) ndp.push_back(dp[j*2+1-x]);
        while(ndp.size() && ndp.back() == 0) ndp.pop_back();
        swap(dp,ndp);
    }
    cout << dp[0].val() << endl;
    return 0;
}