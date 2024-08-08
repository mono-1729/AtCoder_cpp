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

using S = tuple<ll,ll,ll>;
vector<ll> a(200005), b(200005);
S op(S x1, S x2) {
    return min(x1, x2);
} 
S e() {return {0,0,0};}

int main() {
    ll n, k, t; cin >> n >> k >> t;
    vector<tuple<ll,ll,ll>> bap(n);
    rep(i,0,n){
        cin >> a[i] >> b[i];
        bap[i] = {b[i], a[i], i};        
    }
    sort(bap.begin(), bap.end());
    ll sum = 0;
    ll passcnt = 0;
    ll cnt = 0;
    set<tuple<ll, ll, ll>> s;
    segtree<S, op, e> seg(n);
    rep(i,0,n) seg.set(i, {0,a[i]-b[i],i});
    rep(i,0,n){
        // cout << sum << " " << bp[i].first << " " << t << endl;
        auto [bb,aa,idx] = bap[i];
        if(sum + bb <= t){
            sum += bb;
            passcnt++;
            cnt++;
            s.insert({bb,aa,1});
            seg.set(idx, {-1,aa - bb,idx});
        }
    }
    while(passcnt > k){
        if(s.empty()) break;
        auto [x,dist,idx] = seg.all_prod();
        if(x == 0) break;
        seg.set(idx, {0,0,idx});
        s.erase({b[idx], a[idx], 1});
        s.insert({a[idx], a[idx], 0});
        sum += a[idx] - b[idx];
        passcnt--;
        while(sum > t){
            auto [x, idx, y] = *s.rbegin();
            if(y == 0){
                sum -= x;
                cnt--;
                s.erase(*s.rbegin());
            }else{
                sum -= x;
                seg.set(idx, {0,0,idx});
                passcnt--;
                cnt--;
                s.erase(*s.rbegin());
            }
        }
    }
    cout << cnt << endl;
    return 0;
}