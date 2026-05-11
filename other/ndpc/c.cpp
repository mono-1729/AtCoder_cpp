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
    vector<string> s(3);
    rep(i,0,3) cin >> s[i];
    vector<vector<vector<mint>>> dp(s[0].size(),vector<vector<mint>>(s[1].size(),vector<mint>(s[2].size(),0)));
    dp[0][0][0] = 1;
    rep(_,0,n){
        vector<vector<vector<mint>>> ndp(s[0].size(),vector<vector<mint>>(s[1].size(),vector<mint>(s[2].size(),0)));
        rep(i,0,s[0].size())rep(j,0,s[1].size())rep(k,0,s[2].size())rep(l,0,26){
            ll ni = i, nj = j, nk = k;
            if(l == s[0][i]-'a') ni++;
            if(l == s[1][j]-'a') nj++;
            if(l == s[2][k]-'a') nk++;
            if(ni < s[0].size() && nj < s[1].size() && nk < s[2].size()) ndp[ni][nj][nk] += dp[i][j][k];
        }
        swap(dp,ndp);
    }
    mint ans = 0;
    for(auto x: dp)for(auto y: x)for(auto z: y){
        ans += z;
    }
    cout << ans.val() << endl;
    return 0;
}
