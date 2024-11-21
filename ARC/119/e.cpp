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

using S = long long;
S op(S x1, S x2) {
    return min(x1, x2);
}
S e() {return INF;}

int main() {
    ll n; cin >> n;
    vector<ll> a(n);
    ll sum = 0;
    set<ll> st;
    rep(i,0,n) cin >> a[i], st.insert(a[i]);
    vector<ll> u(n-1), d(n-1);
    unordered_map<ll, ll> mp;
    vector<ll> rev(st.size());
    ll idx = 0;
    for(auto x : st){
        mp[x] = idx;
        rev[idx] = x;
        idx++;
    }
    rep(i,0,n-1){
        sum += abs(a[i] - a[i+1]);
        u[i] = max(a[i], a[i+1]);
        d[i] = min(a[i], a[i+1]);
    }
    ll ans = sum;
    ll m = st.size();
    {
        segtree<S, op, e> seg1(m), seg2(m);
        rep(i,0,n-1){
            ll minid = a[i] < a[i+1] ? seg1.prod(mp[u[i]], m) : seg2.prod(mp[u[i]], m);
            chmin(ans, sum - (u[i]-max(d[i], minid))*2);
            // cout << i << " " << sum - (u[i]-max(d[i], minid))*2 << " " << minid << endl;
            chmin(ans, sum - abs(a[i+1] - a[i]) + abs(a[i+1] - a[0]));
            if(i > 0){
                if(a[i] > a[i-1]){
                    if(d[i-1] < seg1.get(mp[u[i-1]])) seg1.set(mp[u[i-1]], d[i-1]);
                }else{
                    if(d[i-1] < seg2.get(mp[u[i-1]])) seg2.set(mp[u[i-1]], d[i-1]);
                }
            }
        }
    }
    { 
        segtree<S, op, e> seg1(m), seg2(m);
        rrep(i,n-2,0){
            ll minid = a[i] < a[i+1] ? seg1.prod(mp[u[i]], m) : seg2.prod(mp[u[i]], m);
            chmin(ans, sum - (u[i]-max(d[i], minid))*2);
            chmin(ans, sum - abs(a[i+1] - a[i]) + abs(a[i] - a[n-1]));
            // cout << i << " " << sum - (u[i]-max(d[i], minid))*2 << " " << minid << endl;
            if(i < n-2){
                if(a[i+1] < a[i+2]){
                    if(d[i+1] < seg1.get(mp[u[i+1]])) seg1.set(mp[u[i+1]], d[i+1]);
                }else{
                    if(d[i+1] < seg2.get(mp[u[i+1]])) seg2.set(mp[u[i+1]], d[i+1]);
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}