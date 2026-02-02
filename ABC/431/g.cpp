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

using S = long long;
S op(S a, S b) {
    return a+b;
} 
ll border = 0;
bool f(S x){
    return x <= border;
}
S e() {return 0;}

int main() {
    ll n, q; cin >> n >> q;
    vector<ll> a(n), rev1(n), rev2(n);
    vector<pll> vec1(n), vec2(n);
    rep(i,0,n){
        cin >> a[i];
        vec1[i] = {a[i], i};
        vec2[i] = {a[i], -i};
    }
    sort(all(vec1));
    sort(all(vec2));
    rep(i,0,n) rev1[vec1[i].second] = i;
    rep(i,0,n) rev2[-vec2[i].second] = i;
    segtree<S, op, e> seg1(vector<S>(n,1)), seg2(vector<S>(n,1));
    vector<pll> ans(q, {-1,-1});
    vector<pll> query(q);
    rep(i,0,q){
        ll k; cin >> k; k--;
        query[i] = {k, i};
    }
    sort(all(query));
    ll ql = 0, qr = q-1;
    ll l = 0, r = n*(n-1)/2-1;
    rep(i,0,n){
        ll xl = lower_bound(all(vec1), pll{a[i], -1LL}) - vec1.begin();
        ll xr = upper_bound(all(vec2), pll{a[i], INF}) - vec2.begin();
        ll nl = seg1.prod(0, xl);
        ll nr = seg2.prod(xr, n);
        while(nl && ql < q && query[ql].first < l+nl){
            border = query[ql].first - l;
            ll id = query[ql].second;
            // cout << "border: " << border << " l: " << l << " nl: " << nl << "\n";
            ans[id] = {i,vec1[seg1.max_right<f>(0)].second};
            // cout << "id: " << id << " ans: " << ans[id].first << " " << ans[id].second << " " << xl << " " << seg.max_right<f>(0) << "\n";
            ql++;
        }
        while(nr && qr >= 0 && query[qr].first > r - nr){
            border = r - query[qr].first;
            ll id = query[qr].second;
            ans[id] = {i,-vec2[seg2.min_left<f>(n)-1].second};
            // cout << "id: " << id << " ans: " << ans[id].first << " " << ans[id].second << "\n";
            qr--;
        }
        l += nl;
        r -= nr;
        seg1.set(rev1[i], 0);
        seg2.set(rev2[i], 0);
    }
    rep(i,0,n-1){
        if(vec1[i].first == vec1[i+1].first){
            ll id1 = vec1[i].second;
            ll id2 = vec1[i+1].second;
            if(id1 > id2) swap(id1, id2);
            rep(j,0,q){
                if(ans[j].first == -1) ans[j] = {id1, id2};
            }
            break;
        }
    }
    for(auto [x,y]: ans){
        cout << x+1 << " " << y+1 << "\n";
    }
    return 0;
}