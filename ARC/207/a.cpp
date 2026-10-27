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

int main() {
    ll n, x; cin >> n >> x;
    ll sum = 0;
    vector<pll> v;
    rep(i,0,n){
        ll a; cin >> a;
        sum += a;
        v.push_back({a,1});
        v.push_back({i,0});
    }

    ll al = n*(n-1)/2, need = sum-x;
    if(need <= 0){
        mint ans = 1;
        rep(i,1,n+1) ans *= i;
        cout << ans.val() << endl;
        return 0;
    }
    if(need > al){
        cout << 0 << endl;
        return 0;
    }
    sort(all(v),greater<pll>());
    vector<vector<mint>> dp(n+1, vector<mint>(al+1));
    dp[0][0] = 1;
    ll c0 = 0, c1 = 0;
    for(auto [ti, ty]: v){
        vector<vector<mint>> ndp(n+1,vector<mint>(al+1));
        rep(i,0,n+1)rep(j,0,al+1){
            if(dp[i][j] == 0) continue;
            if(ty == 0){
                if(c1-i > 0) ndp[i+1][j+ti] += dp[i][j]*(c1-i);
                ndp[i][j] += dp[i][j];
            }else{
                if(c0-i > 0) ndp[i+1][j+ti] += dp[i][j]*(c0-i);
                ndp[i][j] += dp[i][j];
            }
        }
        if(ty) c1++;
        else c0++;
        swap(dp,ndp);
    }
    mint ans = 0;
    rep(i,need,al+1) ans += dp[n][i];
    cout << ans.val() << endl;
}