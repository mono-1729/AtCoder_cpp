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
    ll n, m; cin >> n >> m;
    vector<mint> dp(n+10);
    vector<vector<mint>> sum(n+10,vector<mint>(4,0)), mi(m,vector<mint>(4,0));
    vector<mint> mi_sum(4);
    dp[n] = sum[n][n%4] = 1;
    vector<pll> event;
    rep(i,0,m){
        ll l, r; cin >> l >> r;
        l--;
        if(r-l >= 2){
            event.push_back({r-2,i});
            event.push_back({l-1,-i-1});
        }
    }
    sort(all(event));
    mint c = 0;
    rrep(i,n-1,0){
        while(!event.empty() && event.back().first >= i){
            auto [x,y] = event.back(); event.pop_back();
            if(y >= 0){
                c++;
                rep(j,0,4) mi[y][j] = sum[i+3][(j+2)%4]-sum[i+3][j];
                rep(j,0,4) mi_sum[j] += mi[y][j];
            }else{
                c--;
                rep(j,0,4) mi_sum[j] -= mi[-y-1][j];
            }
        }
        mint all = sum[i+2][(i+2)%4]-sum[i+4][i%4];
        dp[i] = dp[i+1]+c*all-mi_sum[i%4];
        rep(j,0,4) sum[i][j] = sum[i+1][j] + (j == i%4 ? dp[i] : 0);
    }

    cout << dp[0].val() << endl;
    return 0;
}