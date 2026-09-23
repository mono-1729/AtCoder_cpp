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
constexpr ll MOD = 1000000007;
// constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint1000000007;

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
    ll n, k; cin >> n >> k;
    vector<ll> ma; 
    vector<mint> cnt, dp;
    {
        ll now = n;
        while(now){
            ll x = n/now;
            ll l = n/(x+1);
            ma.push_back(x);
            cnt.push_back(now-l);
            now = l;
        }
    }
    dp = cnt;
    ll m = ma.size();

    rep(_,0,k-1){
        vector<mint> ndp(m);
        ll now = n;
        rep(i,0,m){
            ndp.back() += dp[i];
            if(i != m-1) ndp[m-i-2] -= dp[i];
        }
        rrep(i,m-1,1) ndp[i-1] += ndp[i];
        rep(i,0,m) ndp[i] *= cnt[i];

        swap(dp,ndp);
    }
    
    mint ans = 0;
    for(auto x: dp) ans += x;
    cout << ans.val() << endl; 
    return 0;
}