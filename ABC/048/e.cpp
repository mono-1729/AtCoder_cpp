#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <stdlib.h>
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


ll powMod(ll x, ll n, ll mod) {
    if (n == 0) return 1 % mod;
    ll val = powMod(x, n / 2, mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}

int main() {
    ll n, p; cin >> n >> p;
    priority_queue<pll,vector<pll>,greater<pll>> pq;
    vector<ll> sum(n);
    vector<ll> inv(n+1);
    rep(i,1,n+1) inv[i] = powMod(i,p-2,p);
    ll now = 0;
    ll pre_sum = 0;
    if(n%2 == 0) now = (n/2)*(n/2+1);
    else now = (n/2+1)*(n/2+1);
    rep(i,1,n+1){
        sum[0]++;
        ll r = now/i;
        if(r < n) sum[r]--;
        if(r < n) pq.push({(r+1)*i,r+1});
    }
    rep(i,1,n) sum[i] += sum[i-1];
    ll all = 1;
    rep(i,0,n){
        all *= sum[i]-(n-i-1);
        all %= p;
    }
    ll ans = (all*now)%p;
    while(!pq.empty()){
        pre_sum = all;
        auto [__,id_] = pq.top();
        while(!pq.empty()){
            auto [_,id] = pq.top();
            if(_ != __) break;
            pq.pop();
            ll cnum = _/id;
            all *= inv[sum[id-1]-(n-1-(id-1))];
            all %= p;
            sum[id-1]++;
            all *= sum[id-1]-(n-1-(id-1));
            all %= p;
            if(id < n) pq.push({(id+1)*cnum,id+1});
        }
        ll nnum = (all-pre_sum+p)%p;
        ans += nnum*__;
        ans %= p;
    }
    cout << ans << endl;
    return 0;
}