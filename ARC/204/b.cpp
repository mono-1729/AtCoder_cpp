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
    ll n, k; cin >> n >> k;
    vector<ll> p(n*k);
    rep(i,0,n*k) cin >> p[i], p[i]--;
    vector<ll> check(n*k);
    ll ans = 0;
    vector<vector<ll>> nxt(n);
    rep(s,0,n*k){
        if(check[s]) continue;
        vector<ll> vec;
        ll now = s;
        while(!check[now]){
            vec.push_back(now);
            check[now] = 1;
            now = p[now];
        }
        ll m = vec.size();
        vector<vector<ll>> dp(m+1,vector<ll>(m+1));
        rrep(i,m-1,0){
            nxt[vec[i]%n].push_back(i);
            rep(j,i+2,m+1){
                chmax(dp[i][j], max(dp[i+1][j], dp[i][j-1]));
                if(vec[i]%n == vec[j-1]%n) chmax(dp[i][j],dp[i+1][j]+1);
                for(auto x: nxt[vec[i]%n]){
                    if(x == i) continue;
                    chmax(dp[i][j], dp[i][x+1]+dp[x][j]); 
                }
            }
        }
        ans += dp[0][m];
        rep(i,0,m) nxt[vec[i]%n].clear();
    }
    cout << ans << endl;
    return 0;
}