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
    ll d; cin >> d;
    string n; cin >> n;
    vector<vector<mint>> dp(d,vector<mint>(2,0));
    dp[0][0] = 1;
    for(auto x: n){
        ll b = x-'0';
        vector<vector<mint>> ndp(d,vector<mint>(2,0));
        rep(i,0,d){
            rep(j,0,b){
                ndp[(i+j)%d][1] += dp[i][0]+dp[i][1];
            }
            ndp[(i+b)%d][0] += dp[i][0];
            rep(j,b,10){
                ndp[(i+j)%d][1] += dp[i][1]; 
            }
        }
        swap(dp,ndp);
    }
    cout << (dp[0][0]+dp[0][1]-1).val() << endl;
    return 0;
}