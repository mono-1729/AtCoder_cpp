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
#define ull unsigned long long
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
    ll n, k, seed, m; cin >> n >> k >> seed >> m;
    vector<ll> b(m), v(k);
    rep(i,0,m) cin >> b[i];
    rep(i,0,k) cin >> v[i];
    vector<ll> a(n);
    {
        unsigned ll state = seed;
        rep(i,0,n){
            if(i < m) a[i] = b[i];
            else{
                ull x = ((state>>18)^state)>>27;
                x %= (1LL<<32);
                ull r = state>>59;
                ull y = ((x>>r)+(x<<(32-r)));
                y %= (1LL<<32);
                a[i] = y%k;
                state = state*6364136223846793005+2026081520260815;
            }
        }
    }
    vector<vector<ll>> cnt(k,vector<ll>(k,0)),sa(k,vector<ll>(k*2,0));
    rep(i,0,k)rep(j,0,k*2){
        if(v[j%k] != v[(i+j)%k]) sa[i][j] = 1;
    }
    rep(i,0,n-1){
        ll x = (a[i+1]+k-a[i])%k;
        cnt[x][a[i]%k]++;
    }
    vector<ll> ans(k);
    rep(j,0,k){
        if(v[(a[0]+j)%k]) ans[j]++;
        if(v[(a.back()+j)%k]) ans[j]++;
    }
    rep(i,0,k){
        reverse(all(cnt[i]));
        vector<ll> res = convolution_ll(cnt[i],sa[i]);
        rep(j,0,k) ans[j] += res[k-1+j];
    }

    rep(i,0,k) cout << ans[i]/2 << endl;
    return 0;
}