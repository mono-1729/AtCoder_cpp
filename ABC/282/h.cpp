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
    ll n, s; cin >> n >> s;
    vector<ll> a(n), b(n), bsum(n+1,0);
    rep(i,0,n) cin >> a[i];
    rep(i,0,n) cin >> b[i], bsum[i+1] = b[i];
    rep(i,0,n) bsum[i+1] += bsum[i];
    vector<ll> ml(n), mr(n);
    {
        vector<pll> ap(n);
        rep(i,0,n) ap[i] = {a[i],i};
        sort(all(ap));
        set<ll> st;
        st.insert(n);
        st.insert(-1);
        rep(i,0,n){
            auto [num, id] = ap[i];
            auto it = st.lower_bound(id);
            mr[id] = *it-1;
            it = prev(it);
            ml[id] = *it+1;
            st.insert(id);
        }
    }
    ll ans = 0;
    rep(i,0,n){
        if(a[i] > s) continue;
        if(i-ml[i] < mr[i]-i){
            rep(l,ml[i],i+1){
                ll border = s-a[i];
                ll r = upper_bound(all(bsum), bsum[l]+border) - bsum.begin();
                if(i+1 < r) ans += min(r,mr[i]+2)-i-1;
            }
        }else{
            rep(r,i,mr[i]+1){
                ll border = s-a[i];
                ll l = lower_bound(all(bsum), bsum[r+1]-border) - bsum.begin();
                if(l <= i) ans += i+1-max(l,ml[i]);
                // cout << i << " " << l << " " << r << endl;
            }
        }
    }
    cout << ans << endl;
    return 0;
}