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
    ll n; cin >> n;
    vector<ll> x1(n), x2(n);
    rep(i,0,n) cin >> x1[i];
    rep(i,0,n) cin >> x2[i];
    mint ans = 0;
    vector<vector<ll>> d1(n,{INF,INF}), d2(n,{INF,INF});
    auto solve = [&](auto solve, ll l, ll r) -> void {
        if(l+1 == r){
            ans += x1[l]*3+x2[l]*3;
            return;
        }
        rep(i,l,r) d1[i][0] = d1[i][1] = d2[i][0] = d2[i][1] = INF;
        ll mid = (l+r)/2;
        ll sz = (r-mid)*2;
        vector<pll> vec(sz);
        vector<ll> diff(sz);
        vector<mint> sum1(sz+1),sum2(sz+1);
        d1[mid][0] = x1[mid], d2[mid][1] = x2[mid];
        d1[mid][1] = d2[mid][0] = x1[mid]+x2[mid];
        rep(i,mid+1,r){
            d1[i][0] = min(d1[i-1][0]+x1[i],d1[i-1][1]+x1[i]+x2[i]);
            d1[i][1] = min(d1[i-1][1]+x2[i],d1[i-1][0]+x1[i]+x2[i]);
            d2[i][0] = min(d2[i-1][0]+x1[i],d2[i-1][1]+x1[i]+x2[i]);
            d2[i][1] = min(d2[i-1][1]+x2[i],d2[i-1][0]+x1[i]+x2[i]);
        }
        rep(i,mid,r){
            vec[(i-mid)*2] = {d1[i][0], d2[i][0]};
            vec[(i-mid)*2+1] = {d1[i][1], d2[i][1]};
        }
        sort(all(vec), [](const auto x, const auto y){
            return x.first-x.second < y.first-y.second;
        });
        rep(i,0,sz){
            diff[i] = vec[i].first-vec[i].second;
            sum1[i+1] = sum1[i]+vec[i].first;
            sum2[i+1] = sum2[i]+vec[i].second;
        } 
        d1[mid-1][0] = x1[mid-1], d2[mid-1][1] = x2[mid-1];
        d1[mid-1][1] = d2[mid-1][0] = x1[mid-1]+x2[mid-1];
        rrep(i,mid-2,l){
            d1[i][0] = min(d1[i+1][0]+x1[i],d1[i+1][1]+x1[i]+x2[i]);
            d1[i][1] = min(d1[i+1][1]+x2[i],d1[i+1][0]+x1[i]+x2[i]);
            d2[i][0] = min(d2[i+1][0]+x1[i],d2[i+1][1]+x1[i]+x2[i]);
            d2[i][1] = min(d2[i+1][1]+x2[i],d2[i+1][0]+x1[i]+x2[i]);
        }
        rep(i,l,mid)rep(j,0,2){
            ll x = d1[i][j], y = d2[i][j];
            ll id = lower_bound(all(diff),y-x) - diff.begin();
            x %= MOD, y %= MOD;
            ans += (sum1[id]+id*x)*2;
            ans += (sum2[sz]-sum2[id]+(sz-id)*y)*2;
        }
        solve(solve,l,mid);
        solve(solve,mid,r);
    };
    solve(solve,0,n);
    cout << ans.val() << endl;
    return 0;
}