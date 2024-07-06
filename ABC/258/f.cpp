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
constexpr ll INF = 1LL<<62;
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
    int t; cin >> t;
    auto solve_sub = [&] (ll sx, ll sy, ll gx, ll gy, ll b) -> ll {
        ll res = INF;
        vector<tuple<ll,ll,ll>> st,gt;
        if((sx == gx && sx%b == 0) || (sy == gy && sy%b == 0)) res = abs(sx-gx)+abs(sy-gy);
        if(sx%b == 0){
            st.push_back({sx,(sy/b)*b,sy-(sy/b)*b});
            st.push_back({sx,(sy/b+1)*b,(sy/b+1)*b-sy});
        }
        if(sy%b == 0){
            st.push_back({(sx/b)*b,sy,sx-(sx/b)*b});
            st.push_back({(sx/b+1)*b,sy,(sx/b+1)*b-sx});
        }
        if(gx%b == 0){
            gt.push_back({gx,(gy/b)*b,gy-(gy/b)*b});
            gt.push_back({gx,(gy/b+1)*b,(gy/b+1)*b-gy});
        }
        if(gy%b == 0){
            gt.push_back({(gx/b)*b,gy,gx-(gx/b)*b});
            gt.push_back({(gx/b+1)*b,gy,(gx/b+1)*b-gx});
        }
        for(auto [x1,y1,d1] : st)for(auto [x2,y2,d2] : gt){
            chmin(res,d1+d2+abs(x1-x2)+abs(y1-y2));
        }
        return res;
    };
    while(t--){
        ll b, k, sx, sy, gx, gy; cin >> b >> k >> sx >> sy >> gx >> gy;
        ll ans = (abs(sx - gx) + abs(sy - gy)) * k;
        vector<tuple<ll,ll,ll>> st,gt;
        st.push_back({(sx/b)*b,sy,(sx-(sx/b)*b)*k});
        st.push_back({(sx/b+1)*b,sy,((sx/b+1)*b-sx)*k});
        swap(sx,sy);
        st.push_back({sy,(sx/b)*b,(sx-(sx/b)*b)*k});
        st.push_back({sy,(sx/b+1)*b,((sx/b+1)*b-sx)*k});
        swap(sx,gx);swap(sy,gy);
        gt.push_back({(sx/b)*b,sy,(sx-(sx/b)*b)*k});
        gt.push_back({(sx/b+1)*b,sy,((sx/b+1)*b-sx)*k});
        swap(sx,sy);
        gt.push_back({sy,(sx/b)*b,(sx-(sx/b)*b)*k});
        gt.push_back({sy,(sx/b+1)*b,((sx/b+1)*b-sx)*k});
        for(auto [x1,y1,d1] : st)for(auto [x2,y2,d2] : gt){
            chmin(ans,d1+d2+solve_sub(x1,y1,x2,y2,b));
            // cout << ans << " " << x1  << " " << y1 << " " << d1 << " " << x2 << " " << y2 <<  " " << d2 << endl;
        }
        cout << ans << endl;
    }
    return 0;
}