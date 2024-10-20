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
    ll l = 0, r = 1;
    ll ans = 0;
    rep(i,0,q){
        char h; ll  t; cin >> h >> t;
        t--;
        if(h == 'R'){
            if(r < l){
                if(r <= t && t < l) ans += t-r;
                else if(t < r) ans += r-t;
                else ans += r+n-t;
            }else{
                if(l <= t && t < r) ans += r-t;
                else if(t < l) ans += t+n-r;
                else ans += t-r;
            }
            r = t;
        }
        if(h == 'L'){
            if(r < l){
                if(r <= t && t < l) ans += l-t;
                else if(t < r) ans += t+n-l;
                else ans += t-l;
            }else{
                if(l <= t && t < r) ans += t-l;
                else if(t < l) ans += l-t;
                else ans += l+n-t;
            }
            l = t;
        }
    }
    cout << ans << endl;
    return 0;
}