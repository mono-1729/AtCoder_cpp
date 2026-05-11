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
    ll n, d; cin >> n >> d;
    vector<ll> cnt(7,0);
    while(d%2 == 0){
        cnt[2]++;
        d /= 2;
    }
    while(d%3 == 0){
        cnt[3]++;
        d /= 3;
    }
    while(d%5 == 0){
        cnt[5]++;
        d /= 5;
    }
    if(d != 1){
        cout << 0 << endl;
        return 0;
    }
    ll c2 = cnt[2], c3 = cnt[3], c5 = cnt[5];
    ld x6 = 1/(ld)6.0;
    vector<vector<vector<ld>>> dp(c2+1,vector<vector<ld>>(c3+1,vector<ld>(c5+1)));
    dp[0][0][0] = 1;
    rep(_,0,n){
        vector<vector<vector<ld>>> ndp(c2+1,vector<vector<ld>>(c3+1,vector<ld>(c5+1)));
        rep(i,0,c2+1)rep(j,0,c3+1)rep(k,0,c5+1){
            ndp[i][j][k] += dp[i][j][k]*x6;
            ndp[min(c2,i+1)][j][k] += dp[i][j][k]*x6;
            ndp[i][min(c3,j+1)][k] += dp[i][j][k]*x6;
            ndp[min(c2,i+2)][j][k] += dp[i][j][k]*x6;
            ndp[i][j][min(c5,k+1)] += dp[i][j][k]*x6;
            ndp[min(c2,i+1)][min(c3,j+1)][k] += dp[i][j][k]*x6;
        }
        swap(dp,ndp);
    }
    // cout << c2 << " " << c3 << " " << c5 << endl;
    cout << dp[c2][c3][c5] << endl;
    return 0;
}