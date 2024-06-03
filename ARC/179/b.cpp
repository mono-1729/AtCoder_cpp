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
    ll m,n;cin>>m>>n;
    vector<ll> x(m);
    vector<ll> bit(m,0);
    rep(i,0,m){
        cin>>x[i];
        x[i]--;
        bit[x[i]] |= 1<<i;
    }
    vector<vector<mint>> dp(n+1,vector<mint>(1<<m,0));
    dp[0][(1<<m)-1] = 1;
    rep(i,0,n){
        rep(j,0,1<<m){
            rep(k,0,m){
                if(j & (1<<k)){
                    ll nbit = j;
                    nbit &= ~(1<<k);
                    nbit |= bit[k];
                    dp[i+1][nbit] += dp[i][j];
                }
            }
        }
    }
    mint ans = 0;
    rep(i,0,1<<m){
        ans += dp[n][i];
    }
    cout << ans.val() << endl;
    return 0;
}