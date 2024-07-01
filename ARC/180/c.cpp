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
constexpr ll MOD = 1000000007;
//constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint1000000007;

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
    ll n; cin >> n;
    vector<ll> a(n);
    rep(i, 0, n) cin >> a[i];
    vector<vector<mint>> dp(n, vector<mint>(2001, 0));
    unordered_map<ll, ll> mp;
    mp[0] = 1;
    rep(i,0,n){
        if(mp.find(a[i]) == mp.end()){
            mp[a[i]] = 1;
            dp[i][a[i]+1000] = 1;
        }
    }
    rep(i, 0, n){
        rep(j, 0, 2001){
            unordered_map<ll, ll> mp2;
            mp2[0] = 1;
            rep(k, i+1, n){
                if(j+a[k] < 0) continue;
                if(j+a[k] > 2000) continue;
                if(j == 1000 && mp2[a[k]] == 1) continue;
                mp2[a[k]] = 1;
                dp[k][j+a[k]] += dp[i][j];
            }
        }
    }
    mint ans = 0;
    rep(i,0,n)rep(j,0,2001){
        if(j == 1000+a[i]) continue;
        ans += dp[i][j];
        //if(dp[i][j]!=0) cout << i << " " << j-1000 << " " << dp[i][j].val() << endl;
    }
    ans++;
    cout << ans.val() << endl;
    return 0;
}