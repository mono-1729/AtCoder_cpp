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
    ll h, w, n; cin >> h >> w >> n;
    vector<vector<ll>> c(h,vector<ll>(w));
    vector<vector<ll>> nr(1<<h,vector<ll>(10)), nc(1<<w,vector<ll>(10)); 
    rep(i,0,h){
        string s; cin >> s;
        rep(j,0,w){
            c[i][j] = s[j]-'0';
            rep(bit,0,1<<h){
                if(bit>>i&1) nr[bit][c[i][j]] |= 1<<j;
            }
            rep(bit,0,1<<w){
                if(bit>>j&1) nc[bit][c[i][j]] |= 1<<i;
            }
        }
    }
    vector<mint> dp(1<<h,0);
    dp[(1<<h)-1] = 1;
    rep(_,0,n){
        vector<mint> dpw(1<<w,0);
        rep(bit,0,1<<h){
            if(dp[bit] == 0) continue;
            rep(num,0,10){
                if(nr[bit][num] == 0) continue;
                dpw[nr[bit][num]] += dp[bit];
            }
        }
        vector<mint> ndp(1<<h,0);
        rep(bit,0,1<<w){
            if(dpw[bit] == 0) continue;
            rep(num,0,10){
                if(nc[bit][num] == 0) continue;
                ndp[nc[bit][num]] += dpw[bit];
            }
        }
        swap(dp,ndp);
    }
    mint ans = 0;
    for(auto x: dp) ans += x;
    cout << ans.val() << endl;
    return 0;
}