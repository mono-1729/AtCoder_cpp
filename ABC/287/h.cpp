#include <bits/stdc++.h>
#include <stdlib.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define inr(l, x, r) (l <= x && x < r)
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

ll powMod(ll x, ll n, ll mod) {
    if (n == 0) return 1 % mod;
    ll val = powMod(x, n / 2, mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}

vector<bitset<2000>> dp(2000);

int main() {
    ll n, m; cin >> n >> m;
    rep(i,0,m){
        ll a, b; cin >> a >> b;
        a--;b--;
        dp[a][b] = 1;
    }
    ll q; cin >> q;
    vector<ll> ans(q,-1);
    vector<ll> s(q), t(q);
    rep(i,0,q) cin >> s[i] >> t[i], s[i]--, t[i]--;
    rep(k,0,n){
        rep(i,0,n){
            if(dp[i][k]) dp[i] |= dp[k];
        }
        rep(i,0,q){
            if(ans[i] != -1 || s[i] > k || t[i] > k) continue;
            if(dp[s[i]][t[i]]) ans[i] = k+1;
        }
    }
    for(auto x: ans) cout << x << endl;
    return 0;
}