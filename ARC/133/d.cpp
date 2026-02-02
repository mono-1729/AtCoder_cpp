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

int main() {
    ll l, r, v; cin >> l >> r >> v;
    r++;
    map<tuple<ll,ll,ll,ll,ll,ll,ll,ll,ll,ll>,mint> mp;
    set<tuple<ll,ll,ll,ll,ll,ll,ll,ll,ll,ll>> check;
    ll l1, r1, l2, r2;
    auto solve = [&](auto solve, ll okl1, ll okr1, ll okl2, ll okr2, ll x, ll dig) -> mint {
        tuple<ll,ll,ll,ll,ll,ll,ll,ll,ll,ll> query = {l1,r1,l2,r2,okl1,okr1,okl2,okr2,x,dig};
        if(dig == -1) return 1;
        if(check.find(query) != check.end()) return mp[query];
        mint res = 0;
        rep(b1,0,2)rep(b2,0,2){
            if((x>>dig&1) != (b1^b2)) continue;
            if(!okl1 &&  (l1>>dig&1) && !b1) continue;
            if(!okl2 &&  (l2>>dig&1) && !b2) continue;
            if(!okr1 && !(r1>>dig&1) && b1) continue;
            if(!okr2 && !(r2>>dig&1) && b2) continue;
            auto [nokl1,nokl2,nokr1,nokr2] = make_tuple(okl1,okl2,okr1,okr2);
            nokl1 |= (b1 && !(l1>>dig&1));
            nokl2 |= (b2 && !(l2>>dig&1));
            nokr1 |= (!b1 && (r1>>dig&1));
            nokr2 |= (!b2 && (r2>>dig&1));
            res += solve(solve,nokl1,nokr1,nokl2,nokr2,x,dig-1);
        }
        // cout << l1 << " " << r1 << " " << l2 << " " << r2 << " " << okl1 << " " << okr1 << " " << okl2 << " " << okr2 << " " << res.val() << endl;
        check.insert(query);
        return mp[query] = res;
    };
    mint ans = 0;
    if(v == 0){
        mint x = r/4-(l%4 <= 0 ? l/4: l/4+1);
        ans += x*(x+1)/2;
        x = (r-2)/4-(l%4 <= 2 ? l/4: l/4+1);
        ans += x*(x+1)/2;
    }
    if(v == 1){
        mint x = r/4-(l%4 <= 0 ? l/4: l/4+1)+1, y = (r-2)/4-(l%4 <= 2 ? l/4: l/4+1)+1;
        ans += x*y;
    }
    if(l <= (v>>2)*4+1 && (v>>2)*4+1 <= r && (v&3) == 0) ans += r/4-(l%4 <= 0 ? l/4: l/4+1)+1;
    if(l <= (v>>2)*4+1 && (v>>2)*4+1 <= r && (v&3) == 1) ans += (r-2)/4-(l%4 <= 2 ? l/4: l/4+1)+1;
    if(l <= (v>>2)*4+3 && (v>>2)*4+3 <= r && (v&3) == 3) ans += r/4-(l%4 <= 0 ? l/4: l/4+1)+1;
    if(l <= (v>>2)*4+3 && (v>>2)*4+3 <= r && (v&3) == 2) ans += (r-2)/4-(l%4 <= 2 ? l/4: l/4+1)+1;
    // cout << ans.val() << endl;
    if((v&3) == 0 && v != 0){
        l1 = l2 = l%4 <= 1 ? l/4: l/4+1;
        r1 = r2 = (r-1)/4;
        ans += solve(solve,0,0,0,0,v/4LL,60)/2;
        l1 = l2 = l/4;
        r1 = r2 = (r-3)/4;
        ans += solve(solve,0,0,0,0,v/4LL,60)/2;
    }
    if((v&3) == 3){
        l1 = l%4 <= 1 ? l/4: l/4+1;
        r1 = (r-1)/4;
        l2 = l/4;
        r2 = (r-3)/4;
        ans += solve(solve,0,0,0,0,v/4LL,60);
    }
    cout << ans.val() << endl;
    return 0;
}