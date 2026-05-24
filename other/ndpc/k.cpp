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

//https://codeforces.com/contest/1856/problem/E2
//https://codeforces.com/contest/1856/submission/219130190
const ll _max_len=4e6+10;
template<ll _len=1>
std::vector<bool> fast_subset_sub_solver(std::vector<ll> &p,ll sum=-1){
    if(sum==-1){
        sum=0;
        for(auto x:p){
            assert(x>=0);
            sum+=x;
        }
    }
    assert(sum<=_max_len);
    if(sum>=_len){
        return fast_subset_sub_solver<std::min(_max_len,2*_len)>(p,sum);
    }
    for(auto x:p) assert(x>=0);
    std::bitset<_len> dp;
    std::vector<ll> q(sum+1);
    for(auto x:p) q[x]++;
    dp[0]=1;
    for(ll i=1;i<=sum;i++){
        if(q[i]>=1){
            if(0==(q[i]&1)) q[i]--,dp=(dp|(dp<<i));
            q[i]--,dp=(dp|(dp<<i));
            if(i*2<=sum&&2<=q[i]) q[i*2]+=q[i]/2;
        }
    }
    std::vector<bool> res(sum+1);
    for(ll i=0;i<=sum;i++) res[i]=dp[i];
    return res;
}

int main() {
    ll n; cin >> n;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    ll sum = 0;
    rep(i,0,n) sum += a[i], a.push_back(a[i]);
    auto res = fast_subset_sub_solver(a);
    ll ans = 0;
    rep(i,0,sum+1){
        if(res[sum-i] || res[sum+i]) ans++;
    }
    cout << ans << endl;
    return 0;
}