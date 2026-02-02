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
    ll n, q; cin >> n >> q;
    vector<vector<ll>> cnt(n,vector<ll>(n+1,0));
    set<ll> st;
    rep(i,0,q){
        ll l, r; cin >> l >> r;
        l--;
        if(l > 0) cnt[l-1][l+1]++;
        if(r < n) cnt[r-1][r+1]++;
        if(l > 0 && r < n) cnt[l-1][r+1]--;
        if(l) st.insert(l-1);
        if(r < n) st.insert(r-1);
    }
    rep(l,0,n)rep(r,l+1,n+1) cnt[l][r]+=cnt[l][r-1];
    rep(r,0,n+1)rrep(l,r-2,0) cnt[l][r]+=cnt[l+1][r];
    vector<ll> pow2(13,1);
    rep(i,1,13) pow2[i] = pow2[i-1]*2;
    vector<pll> vec;
    {
        ll now = 0;
        for(auto x: st){
            vec.emplace_back(now,x+1);
            now = x+1;
        }
        vec.emplace_back(now,n);
    }
    ll m = vec.size();
    ll d;
    rep(i,0,13){
        if(pow2[i] >= m){
            d = i;
            break;
        }
    }
    if(d == 0){
        cout << 0 << " " << q << endl;
        return 0;
    }
    ll lim = pow2[d]-m;
    vector<vector<ll>> dp(m+1,vector<ll>(lim+1,INF));
    dp[0][0] = 0;
    rep(i,0,m)rep(j,0,lim+1){
        if(j < lim) chmin(dp[i+1][j+1],dp[i][j]);
        if(i < m-1) chmin(dp[i+2][j],dp[i][j]+cnt[vec[i].first][vec[i+1].second]);
    }
    ll c = INF;
    rep(i,0,lim+1) chmin(c,dp[m][i]);
    cout << d << " " << c*2 << endl;
    // rep(i,0,n){
    //     for(auto x: cnt[i]) cout << x << " ";
    //     cout << endl;
    // }
    // rep(i,0,m+1){
    //     for(auto x: dp[i]) cout << x << " ";
    //     cout << endl;
    // }
    // for(auto x: st) cout << x << " ";
    // cout << endl;
    // cout << lim << " " << m << endl;
    return 0;
}