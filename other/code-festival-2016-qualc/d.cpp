#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <atcoder/all>
using namespace atcoder;
using namespace boost::multiprecision;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
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

ll powMod(ll x, ll n) {
    if (n == 0) return 1 % MOD;
    ll val = powMod(x, n / 2);
    val *= val;
    val %= MOD;
    if (n % 2 == 1) val *= x;
    return val % MOD;
}

int main() {
    ll h,w; cin >> h >> w;
    vector<string> c(h);
    rep(i,0,h) cin >> c[i];
    reverse(c.begin(),c.end());
    ll ans = 0;
    rep(i,0,w-1){
        vector<vector<ll>> dp1(h+1,vector<ll>(2*h+1,0));
        rep(j,0,h)rep(k,0,h) if(c[j][i] == c[k][i+1]) dp1[h-j][k-j+h] += 1;
        rep(j,0,h)rep(k,0,2*h+1) dp1[j+1][k] += dp1[j][k];
        vector<vector<ll>> dp2(h+1,vector<ll>(h+1,INF));
        dp2[0][0] = 0;
        rep(j,0,h+1)rep(k,0,h+1){
            if(j<h) chmin(dp2[j+1][k],dp2[j][k]+dp1[j+1][j-k+h+1]);
            if(k<h) chmin(dp2[j][k+1],dp2[j][k]+dp1[j][j-k+h-1]);
        }
        ans += dp2[h][h];
    }
    cout << ans << endl;
    return 0;
}