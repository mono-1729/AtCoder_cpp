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

ll powMod(ll x, ll n) {
    if (n == 0) return 1 % MOD;
    ll val = powMod(x, n / 2);
    val *= val;
    val %= MOD;
    if (n % 2 == 1) val *= x;
    return val % MOD;
}

int main() {
    ll n, k; cin >> n >> k;
    vector<vector<ll>> c(n,vector<ll>(n));
    rep(i,0,n)rep(j,0,n) cin >> c[i][j];
    vector<vector<vector<ll>>> dp(n,vector<vector<ll>>(1<<(k+1), vector<ll>(n,INF)));
    rep(i,k,n){
        rep(j,0,n){
            if(j < k) dp[i][1<<j][j] = 0;
            else if(j == i) dp[i][1<<k][j] = 0;
            else dp[i][0][j] = 0;
        }
        rep(bit,0,1<<(k+1)){
            ll bit2 = (bit-1)&bit;
            while(bit2 > 0){
                rep(j,0,n) chmin(dp[i][bit][j], dp[i][bit2][j]+dp[i][bit^bit2][j]);
                bit2 = (bit2-1)&bit;
            }
            vector<ll> check(n);
            rep(_,0,n){
                ll v = -1;
                rep(j,0,n){
                    if(!check[j]){
                        if(v == -1 || dp[i][bit][v] > dp[i][bit][j]) v = j;
                    }
                }
                check[v] = 1;
                rep(j,0,n){
                    chmin(dp[i][bit][j], dp[i][bit][v]+c[v][j]);
                }
            }
        }
    }
    ll q; cin >> q;
    while(q--){
        ll s, t; cin >> s >> t;
        s--;t--;
        cout << dp[s][(1<<(k+1))-1][t] << endl;
    }
    return 0;
}