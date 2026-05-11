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
    ll n, m, q; cin >> n >> m >> q;
    vector<pll> rl;
    rep(i,0,m){
        ll a, b; cin >> a >> b;
        a--;
        rl.push_back({b,a});
    }
    sort(all(rl));
    vector<vector<ll>> dp(18,vector<ll>(n+2,n+1));
    {
        ll nxt = 0;
        for(auto [r,l]: rl){
            while(nxt <= n && l >= nxt){
                dp[0][nxt] = r;
                nxt++;
            }
            // cout << "r " << r << endl;
        }
    }
    rep(i,0,17)rep(j,0,n+1){
        dp[i+1][j] = dp[i][dp[i][j]];
    }
    while(q--){
        ll l, r; cin >> l >> r;
        l--;
        ll num = 0;
        ll now = l;
        rrep(bit,17,0){
            // cout << dp[bit][now] <<  " " << bit << " " << now << " " << r << endl;
            if(dp[bit][now] <= r){
                now = dp[bit][now];
                num += 1<<bit;
            }
        }
        cout << num << endl;
    }
    return 0;
}
