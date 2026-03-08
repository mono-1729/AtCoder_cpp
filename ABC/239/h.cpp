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

using mint = modint1000000007;

int main() {
    ll n, m; cin >> n >> m;
    mint inv = ((mint)(n-1)).inv();
    ll b = powl(m,0.67);
    chmin(b,m);
    vector<mint> small(b+1);
    vector<mint> diff(b+3,0);
    mint cur = 0;
    rep(t,1,b+1){
        cur += diff[t];
        small[t] = n+cur;
        small[t] *= inv;

        ll xmax = min(n,b/t);
        rep(x,2,xmax+1){
            ll l = t*x, r = min(b,l+x-1);
            diff[l] += small[t];
            diff[r+1] -= small[t];
        }
    }

    unordered_map<ll,mint> mp;
    mp.reserve((size_t)(m / max(1LL, b)) * 2 + 100);
    mp.max_load_factor(0.7f);

    auto solve = [&](auto& solve, ll x) -> mint {
        if(x <= b) return small[x];
        if(mp.count(x)) return mp[x];
        
        mint res = inv*n;
        ll l = 2;
        while(l <= n){
            ll r = n;
            if(x >= l) chmin(r,x/(x/l));
            res += inv*(r-l+1)*solve(solve,x/l);
            l = r+1;
        }
        return mp[x] = res;
    };

    cout << solve(solve,m).val() << endl;
    return 0;
}