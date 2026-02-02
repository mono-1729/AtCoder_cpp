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

using S = vector<vector<mint>>;
S op(S a, S b) {
    return {
        {a[0][0]*b[0][0]+a[0][1]*b[1][0], a[0][0]*b[0][1]+a[0][1]*b[1][1]},
        {a[1][0]*b[0][0]+a[1][1]*b[1][0], a[1][0]*b[0][1]+a[1][1]*b[1][1]}
    };
} 
S e() {return {{1,0},{0,1}};}

ll maxnum=200005;
vector<ll> fac(maxnum), inv(maxnum), finv(maxnum);
void init_fac(){
    fac[0] = fac[1] = 1;
    inv[1] = 1;
    finv[0] = finv[1] = 1;
    rep(i, 2, maxnum){
        fac[i] = fac[i-1]*i%MOD;
        inv[i] = MOD-MOD/i*inv[MOD%i]%MOD;
        finv[i] = finv[i-1]*inv[i]%MOD;
    }
}
ll nCr(ll n, ll r){
    if(n < 0 or n-r < 0 or r < 0) return 0;
    return fac[n]*(finv[n-r]*finv[r]%MOD)%MOD;
}
ll nHr(ll n, ll r){
    return nCr(n+r-1, r);
}

int main() {
    init_fac();
    ll n, q; cin >> n >> q;
    set<pll> st = {{0,0},{n+1,-1}};
    vector<ll> a(n+2, -1);
    segtree<S,op,e> seg(n+2);
    vector<vector<mint>> dp(n+5,vector<mint>(2,0));
    dp[0][0] = 1;
    rep(i,1,n+5){
        dp[i][0] = dp[i-1][0]+dp[i-1][1];
        dp[i][1] = dp[i-1][0];
    }
    auto calc_num = [&](ll l, ll r, ll s, ll t, ll num) -> mint {
        if(num == -INF){
            if(t != 0) return 0;
            ll id = r-l-s;
            return id < 0 ? 0 : dp[id][0];
        }else if(num >= 0){
            if(r-l == 1){
                if(s*t == 0 && t == num) return 1;
                else return 0;
            }else if(r-l == 2){
                if(num == 0){
                    if(t == 0) return 1;
                    else return 0;
                }else if(num == 1){
                    if(t || s == 0) return 1;
                    else return 0;
                }else return 0;
            }
            ll len = r-l-num+1, cnt = num;
            if(s) len--;
            if(t) len--, cnt--;
            else len--;
            return nCr(len,cnt);
        }else return 0;
    };
    seg.set(n+1, {{calc_num(0,n+1,0,0,-INF),0},{0,0}});
    seg.set(0, {{1,0},{0,0}});
    a[0] = 0;
    while(q--){
        ll x, y; cin >> x >> y;
        if(a[x] != y){
            if(a[x] != -1){
                seg.set(x,e());
                st.erase({x,a[x]});
            }
            if(y != -1){
                auto itr = st.upper_bound({x,INF});
                auto itl = prev(itr);
                auto pl = *itl, pr = *itr;
                ll cnt1 = y-pl.second, cnt2 = pr.second-y;
                {
                    S v = e();
                    rep(i,0,2)rep(j,0,2) v[i][j] = calc_num(pl.first,x,i,j,cnt1);
                    seg.set(x,v);
                }
                {
                    S v = e();
                    rep(i,0,2)rep(j,0,2) v[i][j] = calc_num(x,pr.first,i,j,(pr.first == n+1 ? -INF : cnt2));
                    seg.set(pr.first,v);
                }
                st.insert({x,y});
            }else{
                auto itr = st.upper_bound({x,INF});
                auto itl = prev(itr);
                auto pl = *itl, pr = *itr;
                ll cnt = pr.second-pl.second;
                {
                    S v = e();
                    rep(i,0,2)rep(j,0,2) v[i][j] = calc_num(pl.first,pr.first,i,j,(pr.first == n+1 ? -INF : cnt));
                    seg.set(pr.first,v);
                }
            }
            a[x] = y;
        } 
        cout << seg.all_prod()[0][0].val() << endl;
    }
    return 0;
}