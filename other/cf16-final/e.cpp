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
    ll n, a; cin >> n >> a;
    ll ans = n;
    rep(i,1,40){
        auto f = [&](ll x) -> ll {
            ll now = 1;
            rep(_,0,i+1){
                if(n/x < now) return 1;
                now *= x;
            }
            return now >= n;
        };
        ll ng = 1, ok = n;
        while(ok-ng > 1){
            ll mid = (ok+ng)/2;
            if(f(mid)) ok = mid;
            else ng = mid;
        }
        auto g = [&](ll x) -> ll {
            ll now = 1;
            rep(_,0,x){
                if(n/ok < now) return 1;
                now *= ok;
            }
            rep(_,0,i+1-x){
                if(n/ng < now) return 1;
                now *= ng;
            }
            return now >= n;
        };
        ll l = 0, r = i+1;
        while(r-l > 1){
            ll mid = (r+l)/2;
            if(g(mid)) r = mid;
            else l = mid;
        }
        // cout << i << " " << ng << " " << r << " " << a*i+ng*(i+1)+r << endl;
        chmin(ans,a*i+ng*(i+1)+r);
    }
    cout << ans << endl;
    return 0;
}