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

ll maxnum=500005;
vector<ll> fac(maxnum), inv(maxnum), finv(maxnum);
void init_fac(){
    fac[0] = fac[1] = 1;
    inv[1] = 1;
    finv[0] = finv[1] = 1;
    rep(i, 2, maxnum){
        fac[i] = fac[i-1]*i%MOD;
        inv[i] = MOD-MOD/i*inv[MOD%i]%MOD;
        finv[i] = finv[i-1]*inv[i]%MOD;
    }
}
ll nCr(ll n, ll r){
    if(n < 0 or n-r < 0 or r < 0) return 0;
    return fac[n]*(finv[n-r]*finv[r]%MOD)%MOD;
}
ll nHr(ll n, ll r){
    return nCr(n+r-1, r);
}

int main() {
    init_fac();
    ll t; cin >> t;
    while(t--){
        ll n, k; cin >> n >> k;
        vector<ll> a(n);
        rep(i,0,n) cin >> a[i];
        ll num = 0;
        rep(i,n-k,n) num |= a[i];
        ll n0 = 0, n1 = (1LL<<60)-1, cnt = 0;
        vector<mint> pow2(n+1,1);
        rep(i,0,n) pow2[i+1] = pow2[i]*2;
        mint ans = 0;
        mint comb = 0, div2 = (mint)1/((mint)2);
        ll c1 = -1, c2 = -1;
        auto f = [&](ll x, ll y) -> mint {
            if(c1 == -1){
                rep(i,0,y+1) comb += nCr(x,i);
                c1 = x, c2 = y;
                return comb;
            }
            while(x < c1){
                comb = (comb+nCr(c1-1,c2))/2;
                c1--;
            }
            while(y < c2){
                comb -= nCr(c1,c2);
                c2--;
            }
            return comb;
        };
        rrep(i,n-1,0){
            if(((a[i]&n1)|n0) >= num){
                ans += f(i,k-cnt-1);
                n1 &= a[i];
                if(i == 0 && n0 >= num) ans++;
            }else{
                cnt++;
                n0 = ((a[i]&n1)|n0);
                if(cnt == k){
                    if(n0 >= num) ans++;
                    break;
                }
            }
        }
        cout << ans.val() << endl;
    }
    return 0;
}