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
    cout << fixed << setprecision(15);
    vector<ld> dp(1<<16,INF);
    dp[0] = 0;
    ld div3 = 1/(ld)3.0;
    rep(i,1,1<<16){
        rep(j,1,15){
            if(!(i>>j&1) && !(i>>(j-1)&1) && !(i>>(j+1)&1)) continue;
            ld ok = 0;
            ld cc = 0;
            ld num = 0;
            if((i>>j&1)) ok += div3, cc++;
            if((i>>(j-1)&1)) ok += div3, cc++;
            if((i>>(j+1)&1)) ok += div3, cc++;
            if((i>>j&1)) num += dp[i^(1<<j)]/cc;
            if((i>>(j-1)&1)) num += dp[i^(1<<(j-1))]/cc;
            if((i>>(j+1)&1)) num += dp[i^(1<<(j+1))]/cc;
            num += 1/ok;
            chmin(dp[i],num);
        }
    }

    ll n; cin >> n;
    ll id = 0;
    rep(i,0,n){
        ll x; cin >> x;
        id += 1LL<<x;
    }
    cout << dp[id] << endl;
    return 0;
}