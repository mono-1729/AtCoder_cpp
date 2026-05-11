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
    ll n, l; cin >> n >> l;
    vector<string> w(n);
    vector<vector<ll>> in(9,vector<ll>(1<<8,0));
    rep(i,0,n){
        cin >> w[i];
        ll num = 0;
        for(auto x: w[i]){
            num *= 2;
            if(x == '1') num += 1;
        }
        in[w[i].size()][num] = 1;
    }
    vector<vector<vector<ll>>> ok(1<<7,vector<vector<ll>>(1<<8,{0,0}));
    rep(i,0,1<<7)rep(j,0,1<<8)rep(k,0,2){
        ll num = i*2+k;
        ll next = (j*2)%(1<<8);
        rep(bit,0,7){
            if((j>>bit&1) && in[bit+1][num%(1<<(bit+1))]) next |= 1;
        }
        ok[i][j][k] = next;
    }
    vector<vector<vector<mint>>> dp(l+1,vector<vector<mint>>(1<<7,vector<mint>(1<<8,0)));
    dp[0][0][1] = 1;
    rep(i,0,l)rep(j,0,1<<7)rep(k,0,1<<8){
        rep(p,0,2) dp[i+1][(j*2+p)%(1<<7)][ok[j][k][p]] += dp[i][j][k];
    }

    mint ans = 0;
    rep(j,0,1<<7)rep(k,0,1<<8){
        if(k&1) ans += dp[l][j][k];
    }
    cout << ans.val() << endl;
    return 0;
}