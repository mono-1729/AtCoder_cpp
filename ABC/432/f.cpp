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
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    vector<ll> sum(1<<n, 0);
    rep(i,0,1<<n){
        rep(j,0,n){
            if(i>>j&1) sum[i] += a[j];
        }
    }
    if(sum[(1<<n)-1]%n != 0){
        cout << -1 << endl;
        return 0;
    }
    ll b = sum[(1<<n)-1]/n;
    vector<ll> dp(1<<n, INF), pre(1<<n,-1);
    dp[0] = 0;
    rep(i,0,1<<n){
        ll pc = __builtin_popcount(i);
        ll f = sum[i] == b*pc ? 0 : 1;
        rep(j,0,n){
            if(i>>j&1) continue;
            ll ni = i^(1<<j);
            if(sum[ni] < b*pc) continue;
            if(dp[ni] > dp[i]+f){
                dp[ni] = dp[i]+f;
                pre[ni] = j;
            }
        }
    }
    vector<tuple<ll,ll,ll>> ans;
    {
        vector<ll> vec;
        {
            ll now = (1<<n)-1;
            while(now){
                vec.push_back(pre[now]);
                now ^= 1<<pre[now];
            }
        }
        reverse(all(vec));
        ll now = vec[0], num = a[now];
        // for(auto x: vec) cout << x << " ";
        // cout << endl;
        rep(i,1,vec.size()){
            if(num < b){
                ll idou = b-num;
                ans.push_back({vec[i],now,idou});
                now = vec[i];
                num = a[vec[i]]-idou;
            }else if(num > b){
                ll idou = num-b;
                ans.push_back({now,vec[i],idou});
                now = vec[i];
                num = a[vec[i]]+idou;
            }else{
                now = vec[i];
                num = a[vec[i]];
            }
        }
    }
    cout << ans.size() << endl;
    for(auto [x,y,z]: ans) cout << x+1 << " " << y+1 << " " << z << endl;
    return 0;
}