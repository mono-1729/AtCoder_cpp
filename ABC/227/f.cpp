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
    ll h, w, k_; cin >> h >> w >> k_;
    vector<vector<ll>> a(h, vector<ll>(w));
    vector<ll> nums;
    rep(i, 0, h)rep(j, 0, w){
        cin >> a[i][j];
        nums.push_back(a[i][j]);
    }
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    ll ans = INF;
    for(auto num : nums){
        vector<vector<vector<ll>>> dp(h+1,vector<vector<ll>>(w+1,vector<ll>(h+w,INF)));
        dp[0][1][0] = 0;
        rep(i,0,h)rep(j,0,w)rep(k,0,h+w){
            if(a[i][j] >= num){
                if(k>0){
                    chmin(dp[i+1][j+1][k], dp[i+1][j][k-1] + a[i][j] - num);
                    chmin(dp[i+1][j+1][k], dp[i][j+1][k-1] + a[i][j] - num);
                }
            }
            else{
                chmin(dp[i+1][j+1][k], dp[i+1][j][k]);
                chmin(dp[i+1][j+1][k], dp[i][j+1][k]);
            }
        }
        rep(i,k_,h+w) chmin(ans,num * k_ + dp[h][w][i]);
    }
    cout << ans << endl;
    return 0;
}