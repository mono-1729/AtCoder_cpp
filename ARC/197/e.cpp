#include <bits/stdc++.h>
#include <stdlib.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define inr(l, x, r) (l <= x && x < r)
#define ll long long
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
    ll t; cin >> t;
    while(t--){
        ll n, h, w; cin >> n >> h >> w;
        if(h < 2*n || w < 2*n){
            cout << 0 << endl;
            continue;
        }
        mint ans = 1;
        {
            mint x = (w-n*2+2)*(w-n*2+1)/2;
            ans *= x*x;
            x = (h-n*2+2)*(h-n*2+1)/2;
            ans *= x*x;
        }
        // cout << ans.val() << " ";
        mint cnt = 1;
        rep(i,0,2){
            mint num = 0;
            {
                mint x = 1;
                rep(j,0,4) x *= h-2*n+4-j;
                x /= 24;
                num += x;
            }
            {
                mint x = 1;
                rep(j,0,3) x *= h-2*n+3-j;
                x /= 6;
                num -= x;
            }
            cnt *= num;
            swap(h,w);
        }
        ans -= cnt*2;
        cout << ans.val() << endl;
    }
    return 0;
}