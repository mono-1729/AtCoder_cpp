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
    string s; cin >> s;
    unordered_map<ll,mint> dp;
    ll pow2 = 51*51, pow3 = 51*51*51, pow4 = 51*51*51*51;
    dp[0] = 1;
    rep(i,0,n){
        unordered_map<ll,mint> ndp;
        for(auto [key, val] : dp){
            ll kx = key%pow2, a = (key/pow2)%51, b = (key/pow3)%51, c = (key/pow4)%51, d = i-a-b-c;
            if(s[i] == '?'){
                ndp[kx+a + pow2*(d+1) + pow3*c + pow4*b] += val;
                ndp[kx+b + pow2*c + pow3*(d+1) + pow4*a] += val;
                ndp[kx+c + pow2*b + pow3*a + pow4*(d+1)] += val;
            }else if(s[i] == 'A'){
                ndp[kx+a + pow2*(d+1) + pow3*c + pow4*b] += val;
            }else if(s[i] == 'B'){
                ndp[kx+b + pow2*c + pow3*(d+1) + pow4*a] += val;
            }else {
                ndp[kx+c + pow2*b + pow3*a + pow4*(d+1)] += val;
            }
        }
        swap(dp, ndp);
    }
    mint ans = 0;
    for(auto [key, val] : dp){
        ll kx = key%pow2;
        if(kx >= k) ans += val;
    }
    cout << ans.val() << endl;
    return 0;
}