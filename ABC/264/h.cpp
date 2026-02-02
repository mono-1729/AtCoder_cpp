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
    vector<ll> p(n,-1);
    vector<ll> d(n,0);
    rep(i,1,n) cin >> p[i], p[i]--, d[i] = d[p[i]]+1;
    vector<vector<mint>> dp(n,vector<mint>(21,0)), sum(n,vector<mint>(21,0));
    rep(i,0,n){
        if(d[i] < 20){
            mint now = 1;
            ll j = 0, v = i, pre = -1;
            while(v != -1){
                mint tmp = dp[v][j];
                mint diff;
                if(j == 0) dp[v][j] = 1, diff = 1;
                else{
                    mint x = sum[v][j]-dp[pre][j-1];
                    diff = (dp[pre][j-1]-now)*x;
                    dp[v][j] += diff;
                }
                pre = v;
                v = p[v];
                if(v != -1) sum[v][j+1] += diff;
                j++;
                now = tmp;
            }
        }
        mint ans = 0;
        rep(j,0,20) ans += dp[0][j];
        cout << ans.val() << endl;
    }
    return 0;
}