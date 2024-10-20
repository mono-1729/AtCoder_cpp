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
    ll n, q; cin >> n >> q;
    vector<ll> dp(n,INF);
    dp[1] = 0;
    char lh = 'L'; ll lt = 0;
    rep(__,0,q){
        char h; ll t; cin >> h >> t;
        t--;
        t = (t-lt+n)%n;
        rotate(dp.begin(), dp.begin()+lt, dp.end());
        vector<ll> ndp(n, INF);
        rep(_,0,2){
            reverse(dp.begin()+1, dp.end());
            reverse(ndp.begin()+1, ndp.end());
            t = (n-t)%n;
            rep(i,0,n){
                if(h == lh){
                    if(i <= t) chmin(ndp[(t+1)%n], dp[i]+t+t-i+1);
                    else chmin(ndp[i], dp[i]+t);
                }else{
                    if(i <= t) chmin(ndp[0], dp[i]+t-i);
                    else chmin(ndp[(t+1)%n], dp[i]+n-i+2*t+1);
                }
            }
        }
        swap(dp, ndp);
        rotate(dp.begin(), dp.begin()+(n-lt), dp.end());
        lh = h; lt = (t+lt)%n;
    }
    ll ans = INF;
    rep(i,0,n) chmin(ans, dp[i]);
    cout << ans << endl;
    return 0;
}