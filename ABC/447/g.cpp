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
    ll n; cin >> n;
    vector<vector<pair<ll,array<ll,3>>>> dp(7);
    dp[0].push_back({0,{-1,-1,-1}});
    vector<ll> sz = {1,8,8,8,8,8,1};
    rep(i,0,n){
        ll k, a; cin >> k >> a; k--;
        vector<vector<pair<ll,array<ll,3>>>> ndp(7);
        auto add = [&](ll id, ll val, array<ll,3> v) -> void {
            ll f = 1;
            rep(j,0,ndp[id].size()){
                if(ndp[id][j].second == v){
                    if(ndp[id][j].first >= val) return;
                    ndp[id][j].first = val;
                    f = 0;
                }
            }
            if(f) ndp[id].push_back({val,v});
            sort(all(ndp[id]),greater<>());
            if(ndp[id].size() > sz[id]) ndp[id].pop_back();
        };
        rep(j,0,7){
            for(auto [x,y]: dp[j]){
                add(j,x,y);
                if(j < 6){
                    if(ndp[j+1].size() == sz[j+1] && ndp[j+1].back().first >= x+a) continue;
                    ll f = 0;
                    rep(l,0,3) if(y[l] == k) f = 1;
                    if(f) continue;
                    if(j < 3){
                        array<ll,3> z = y;
                        z[j] = k;
                        add(j+1,x+a,z);
                    }else if(j == 3){
                        array<ll,3> z = {y[2],k,-1};
                        add(j+1,x+a,z);
                    }else if(j < 5){
                        array<ll,3> z = y;
                        z[j-2] = k;
                        add(j+1,x+a,z);
                    }else{
                        add(j+1,x+a,{y[0],y[1],k});
                    }
                }
            }
        }
        swap(dp,ndp);
    }
    if(dp[6].size() == 0) cout << -1 << endl;
    else{
        cout << dp[6][0].first << endl;
        // cout << dp[6][0].second[0] << endl;
        // cout << dp[6][0].second[1] << endl;
        // cout << dp[6][0].second[2] << endl;
    }
    return 0;
}