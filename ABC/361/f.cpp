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
    ll n; cin >> n;
    ll ans = 0;
    ll l = 1, r = 1e9+10;
    while(r-l > 1){
        ll m = (l+r)/2;
        if(m*m <= n) l = m;
        else r = m;
    }
    ans += l;
    unordered_map<ll, ll> mp;
    rep(i,3,60){
        for(int j = 2;;j++){
            ll num = 1;
            bool ok = true;
            rep(k,0,i){
                if(num > n/j +1) {
                    ok = false;
                    break;
                }
                num *= j;
            }
            if(!ok || num > n) {
                break;
            }
            if(mp[num] == 1) continue;
            assert((sqrt((long double)num)-3 < 0 || (sqrt((long double)num)-3)*(sqrt((long double)num)-3)<=num) && (sqrt((long double)num)+4)*(sqrt((long double)num)+4) >=num);
            rep(k,sqrt((long double)num)-3,sqrt((long double)num)+4){
                if(k*k == num){
                    mp[num] = 1;
                    ok = false;
                    break;
                }
            }
            if(ok){
                ans++;
                mp[num] = 1;
            }
        }
    }
    cout << ans << endl;
    return 0;
}