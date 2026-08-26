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

using S = pll;
S op(S a, S b) {
    return {a.first+b.first,a.second+b.second};
} 
bool f(S x){
    return 1;
}
S e() {return {0,0};}

mint solve(vector<ll> a, vector<ll> b, ll k){
    ll n = a.size(), m = b.size();
    vector<tuple<ll,ll,ll>> query(n);
    vector<pll> vv(m);
    vector<ll> bb(m), rev(m), si(m);
    mint res = 0;
    rep(i,0,m) bb[i] = b[(n*i)%m], rev[(n*i)%m] = i, vv[i] = {b[i],i};
    rep(i,0,n) query[i] = {rev[i%m],k/n+(k%n > i ? 1 : 0),a[i]};
    sort(all(query));
    sort(all(vv));
    rep(i,0,m) si[rev[vv[i].second]] = i;
    vector<ll> sum(m+1);
    rep(i,0,m) sum[i+1] = sum[i]+vv[i].first;
    segtree<S,op,e> seg(m);
    ll l = 0, r = 0;
    for(auto [s,len,p]: query){
        ll id = lower_bound(all(vv),make_pair(p,0LL)) - vv.begin();
        ll x = sum[id]+p*(m-id);
        res += (x%MOD)*((len/m)%MOD);
        len %= m;
        if(len == 0) continue;
        ll rr = s+len;
        while(r < rr){
            seg.set(si[r%m],{bb[r%m],1});
            r++;
        }
        while(r > rr){
            r--;
            seg.set(si[r%m],{0,0});
        }
        while(l > s){
            l--;
            seg.set(si[l%m],{bb[l%m],1});
        }
        while(l < s){
            seg.set(si[l%m],{0,0});
            l++;
        }
        auto [ss, cnt] = seg.prod(0,id);
        res += ss+(len-cnt)*p;
        // cout << s << " " << len << " " << p << " " << ss << " " << cnt << endl;
    }
    return res;
}

int main() {
    ll n, m, k; cin >> n >> m >> k;
    vector<ll> a(n), b(m), rev(m);
    rep(i,0,n) cin >> a[i];
    rep(i,0,m) cin >> b[i];
    ll g = gcd(n,m);
    mint ans = 0;
    rep(i,0,g){
        vector<ll> aa, bb;
        for(ll j = i; j < n; j += g) aa.push_back(a[j]);
        for(ll j = i; j < m; j += g) bb.push_back(b[j]);
        ans += solve(aa,bb,k/g+(k%g > i ? 1 : 0));
    }
    cout << ans.val() << endl;
    return 0;
}