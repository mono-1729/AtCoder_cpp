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
    ll n, k; cin >> n >> k;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    sort(a.begin(), a.end());
    vector<vector<pll>> dp(n+1);
    dp[0] = {{0,1}};
    rep(i,0,n){
        vector<pll> use(dp[i].size());
        rep(j,0,dp[i].size()){
            auto [x,y] = dp[i][j];
            use[j] = {x+a[i], y+a[i]};
        }
        int d_idx = 0, u_idx = 0;
        ll cnt = 0;
        auto insert = [&](ll l, ll r) -> void {
            if(dp[i+1].size() == 0) dp[i+1].push_back({l,r});
            else if(dp[i+1].back().second >= l){
                chmax(dp[i+1].back().second,r);
            }
            else{
                cnt += max(0LL,min(a[i],l)-dp[i+1].back().second);
                dp[i+1].push_back({l,r});
            }
        };
        while(d_idx < dp[i].size() || u_idx < dp[i].size()){
            if(d_idx == dp[i].size()){
                insert(use[u_idx].first, use[u_idx].second);
                u_idx++;
            }
            else if(u_idx == dp[i].size()){
                insert(dp[i][d_idx].first, dp[i][d_idx].second);
                d_idx++;
            }
            else if(dp[i][d_idx].first > use[u_idx].first){
                insert(use[u_idx].first, use[u_idx].second);
                u_idx++;
            }
            else{
                insert(dp[i][d_idx].first, dp[i][d_idx].second);
                d_idx++;
            }
        }
        if(cnt >= k){
            ll num = 0;
            rep(j,0,dp[i+1].size()-1){
                for(ll x = dp[i+1][j].second;num < k && x < dp[i+1][j+1].first;x++,num++) cout << x << " ";
            }
            return 0;
        }
    }
    ll num = 0;
    dp[n].push_back({1LL<<62, 1LL<<62});
    rep(j,0,dp[n].size()-1){
        for(ll x = dp[n][j].second;num < k && x < dp[n][j+1].first;x++,num++) cout << x << " ";
    }
    return 0;
}