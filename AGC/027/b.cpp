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
    ll n, c; cin >> n >> c;
    vector<ll> x(n);
    rep(i,0,n) cin >> x[i];
    reverse(all(x));
    vector<__int128_t> sum(n+1,0);
    rep(i,0,n) sum[i+1] = sum[i]+x[i];
    __int128_t ans = INF;
    rep(i,1,n+1){
        __int128_t num = (n+i)*c;
        __int128_t now = 0;
        __int128_t b = n/i;
        rep(j,0,b){
            if(j == 0) num += (sum[now+i]-sum[now])*2;
            num += (sum[now+i]-sum[now])*((j+1)*2+1);
            now += i;
        }
        if(now != n){
            num += (sum[n]-sum[now])*(b*2+3);
        }        
        chmin(ans,num);
    }
    cout << (ll)ans << endl;
    return 0;
}