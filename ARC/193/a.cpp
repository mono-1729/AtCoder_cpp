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
bool f(S x){
    return 1;
}
S e() {return INF;}

int main() {
    ll n; cin >> n;
    vector<ll> w(n);
    rep(i,0,n) cin >> w[i];
    vector<tuple<ll,ll,ll>> vec1(n), vec2(n);
    vector<ll> l(n), r(n);
    rep(i,0,n){
        cin >> l[i] >> r[i];
        vec1[i] = make_tuple(l[i],r[i],w[i]);
        vec2[i] = make_tuple(l[i],r[i],w[i]);
    }
    sort(all(vec1), [](const auto a, const auto b){
        auto [l1, r1, w1] = a;
        auto [l2, r2, w2] = b;
        return r1 < r2;
    });
    sort(all(vec2), [](const auto a, const auto b){
        auto [l1, r1, w1] = a;
        auto [l2, r2, w2] = b;
        return l1 < l2;
    });
    
    segtree<S,op,e> segl(n), segr(n);
    vector<ll> lvec(n), rvec(n);
    rep(i,0,n){
        segl.set(i, get<2>(vec1[i]));
        segr.set(i, get<2>(vec2[i]));
        lvec[i] = get<1>(vec1[i]);
        rvec[i] = get<0>(vec2[i]);
    }

    ll q; cin >> q;
    rep(i,0,q){
        ll s, t; cin >> s >> t;
        s--;t--;
        ll l1 = l[s], r1 = r[s], l2 = l[t], r2 = r[t];
        ll ans = w[s]+w[t];
        if(l1 > l2 || (l1 == l2 && r1 > r2)){
            swap(l1, l2);
            swap(r1, r2);
        }
        if(l1 <= l2 && r2 <= r1){
            ll rx = lower_bound(lvec.begin(), lvec.end(), l1) - lvec.begin();
            ll lx = upper_bound(rvec.begin(), rvec.end(), r1) - rvec.begin();
            ll num = min(segl.prod(0,rx), segr.prod(lx,n));
            if(num == INF){
                cout << -1 << endl;
                continue;
            }else ans += num;
        }else if(l2 <= r1){
            ll rx = lower_bound(lvec.begin(), lvec.end(), l1) - lvec.begin();
            ll lx = upper_bound(rvec.begin(), rvec.end(), r2) - rvec.begin();
            ll num = min(segl.prod(0,rx), segr.prod(lx,n));
            ll rx_ = lower_bound(lvec.begin(), lvec.end(), l2) - lvec.begin();
            ll lx_ = upper_bound(rvec.begin(), rvec.end(), r1) - rvec.begin();
            ll num2 = segl.prod(0,rx_)+segr.prod(lx_,n);
            if(min(num, num2) >= INF){
                cout << -1 << endl;
                continue;
            }else{
                ans += min(num,num2);
            }
        }
        cout << ans << endl;
    }
    return 0;
}