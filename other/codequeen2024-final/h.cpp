#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <atcoder/all>
using namespace atcoder;
using namespace boost::multiprecision;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
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

ll powMod(ll x, ll n) {
    if (n == 0) return 1 % MOD;
    ll val = powMod(x, n / 2);
    val *= val;
    val %= MOD;
    if (n % 2 == 1) val *= x;
    return val % MOD;
}

int main() {
    ll n, k, t; cin >> n >> k >> t;
    vector<ll> a_(n), b_(n), a(n),b(n);
    vector<pll> ab(n);
    rep(i,0,n) cin >> a_[i] >> b_[i];
    rep(i,0,n) ab[i] = {-a_[i]+b_[i],i};
    sort(ab.begin(), ab.end());
    rep(i,0,n){
        auto [_, id] = ab[i];
        a[i] = a_[id];
        b[i] = b_[id];
    }
    ll l = 0, r = n+1;
    while(r-l > 1){
        ll mid = (l+r)/2;
        ll mini = INF;
        vector<ll> bsum(n+1,INF), asum(n+1,INF);
        {
            ll sum = 0;
            priority_queue<ll> pq;
            rep(i,0,n){
                pq.push(b[i]);
                sum += b[i];
                if(pq.size() > min(k,mid)) sum -= pq.top(), pq.pop();
                if(pq.size() == min(k,mid)) bsum[i] = sum;
            }
        }
        {
            ll sum = 0;
            priority_queue<ll> pq;
            rrep(i,n-1,0){
                pq.push(a[i]);
                sum += a[i];
                if(pq.size() > mid - min(mid,k)) sum -= pq.top(),pq.pop();
                if(pq.size() == mid - min(mid,k)) asum[i] = sum;
            }
            if(k >= mid) asum[n] = 0;
        }
        rep(i,0,n) chmin(mini, bsum[i] + asum[i+1]);
        if(mini <= t) l = mid;
        else r = mid;
    }
    cout << l << endl;
    return 0;
}