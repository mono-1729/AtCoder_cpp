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

ll maxnum=400005;
vector<ll> fac_(maxnum), inv_(maxnum), finv_(maxnum);
void init_fac(){
    fac_[0] = fac_[1] = 1;
    inv_[1] = 1;
    finv_[0] = finv_[1] = 1;
    rep(i, 2, maxnum){
        fac_[i] = fac_[i-1]*i%MOD;
        inv_[i] = MOD-MOD/i*inv_[MOD%i]%MOD;
        finv_[i] = finv_[i-1]*inv_[i]%MOD;
    }
}
ll nCr(ll n, ll r){
    if(n < 0 or n-r < 0 or r < 0) return 0;
    return fac_[n]*(finv_[n-r]*finv_[r]%MOD)%MOD;
}
ll nHr(ll n, ll r){
    return nCr(n+r-1, r);
}

vector<mint> calc(ll n){
    vector<mint> res(n+1), pow2(n+1,1);
    rep(i,0,n) pow2[i+1] = pow2[i]*2;
    res[0] = 1;
    res[n] = pow2[n];
    rep(i,0,n){
        res[i] = pow2[n];
        rep(j,1,n+1){
            if(j*(i+1) > n) break;
            if(j*(i+2) <= n) res[i] += pow2[n-(j*(i+2))]*nCr(j+(n-j*(i+2)),j)*(j%2 ? -1: 1);
            if(j*(i+2)-1 <= n) res[i] += pow2[n-(j*(i+2)-1)]*nCr(j-1+(n-j*(i+2)+1),j-1)*(j%2 ? -1: 1);
        }
    }
    // rep(i,0,n+1) cout << res[i].val() << endl;
    return res;
}

int main() {
    init_fac();
    ll n; cin >> n;
    string s; cin >> s;
    vector<mint> ans(n+1,1), fac(n+1,1), finv(n+1,1), pow2(n+1,1), inv2(n+1,1);
    vector<ll> pre(n+1,0);
    rep(i,0,n) pow2[i+1] = pow2[i]*2, inv2[i+1] = inv2[i]/2;
    ll now = 0;
    while(now < n){
        if(s[now] == 'x'){
            fac[now+1] = fac[now];
            finv[now+1] = finv[now];
            now++;
            continue;
        }
        ll r = now;
        while(r < n && s[r] == '.') r++;
        vector<mint> res = calc(r-now);
        rep(i,now,r){
            fac[i+1] = fac[now]*pow2[r-now];
            finv[i+1] = finv[now]*inv2[r-now];
        }
        rep(i,0,r-now+1){
            ans[i]*=res[i]*fac[now]*finv[pre[i]];
            pre[i] = r;
        }
        now = r;
    }
    rep(i,0,n+1) ans[i] *= fac[now]*finv[pre[i]];
    rep(i,1,n+1) cout << (ans[i]-ans[i-1]).val() << endl;
    return 0;
}