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
    int n, wm, cm; cin >> n >> wm >> cm;
    vector<tuple<int,int,int>> wvc(n);
    vector<int> w(n), v(n), c(n+1,IINF);
    rep(i,0,n){
        ll x, y, z; cin >> x >> y >> z;
        wvc[i] = {z-1,x,y};
    }
    sort(all(wvc));
    rep(i,0,n){
        auto [z,x,y] = wvc[i];
        w[i] = x, v[i] = y, c[i] = z;
    }
    vector<vector<vector<int>>> dp(wm+1,vector<vector<int>>(cm+1,vector<int>(2,-IINF)));
    dp[0][0][0] = 0;
    rep(i_,0,n){
        vector<vector<vector<int>>> ndp(wm+1,vector<vector<int>>(cm+1,vector<int>(2,-IINF)));
        rep(i,0,wm+1)rep(j,0,cm+1){
            if(c[i_] == c[i_+1]){
                chmax(ndp[i][j][0], dp[i][j][0]);
                chmax(ndp[i][j][1], dp[i][j][1]);
                if(i+w[i_] <= wm){
                    if(j < cm) chmax(ndp[i+w[i_]][j+1][1],dp[i][j][0]+v[i_]);
                    chmax(ndp[i+w[i_]][j][1],dp[i][j][1]+v[i_]);
                }
            }else{
                chmax(ndp[i][j][0], max(dp[i][j][0],dp[i][j][1]));
                if(i+w[i_] <= wm){
                    if(j < cm)  chmax(ndp[i+w[i_]][j+1][0],dp[i][j][0]+v[i_]);
                    chmax(ndp[i+w[i_]][j][0],dp[i][j][1]+v[i_]);
                }
            }
        }
        swap(dp,ndp);
    }
    int ans = -IINF;
    for(auto x: dp)for(auto y: x)for(auto z: y) chmax(ans,z);
    cout << ans << endl;
    return 0;
}