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

struct ku {
    ll x;
    ll y;
    pll type;
    vector<ku> next(){
        vector<ku> res;
        ll xd = type.first, yd = type.second;
        res.push_back({x+xd,y+yd,{-xd,-yd}});
        res.push_back({x,y,{-xd,yd}});
        res.push_back({x,y,{xd,-yd}});
        res.push_back({x+xd,y,{-xd,yd}});
        res.push_back({x,y+yd,{xd,-yd}});
        res.push_back({x+xd,y,{-xd,-yd}});
        res.push_back({x,y+yd,{-xd,-yd}});
        return res;
    }
};

int main() {
    ll t; cin >> t;
    vector<vector<vector<ku>>> vec(4,vector<vector<ku>>(4));
    vec[0][3].push_back({0,0,{1,1}});
    rep(i,0,3)rep(j,0,4){
        for(auto x: vec[i][j]){
            for(auto nt: x.next())if(nt.type != make_pair(1LL,1LL)){
                ll tx = 0;
                if(nt.type.first == 1) tx += 2;
                if(nt.type.second == 1) tx += 1;
                vec[i+1][tx].push_back(nt);
            }
        }
    }
    auto calc = [&](ll x, ll y, ll dx, ll dy) -> ll {
        if((dx * x)*(dy * y) > 0){
            x = abs(x);
            y = abs(y);
            return min(x,y) * 3 + (max(x,y)-min(x,y)) * 2;
        }else{
            x = abs(x);
            y = abs(y);
            return min(x,y) * 2 + (max(x,y)-min(x,y)) * 2;
        }
    };
    while(t--){
        ll ax, ay, bx, by, cx, cy; cin >> ax >> ay >> bx >> by >> cx >> cy;
        ll x, y;
        pll type;
        if(ax == bx || ax == cx) x = ax;
        else x = cx;
        if(ay == by || ay == cy) y = ay;
        else y = cy;
        if(ax != x) type.first = ax-x;
        if(bx != x) type.first = bx-x;
        if(cx != x) type.first = cx-x;
        if(ay != y) type.second = ay-y;
        if(by != y) type.second = by-y;
        if(cy != y) type.second = cy-y;
        vector<vector<vector<ku>>> nvec(4,vector<vector<ku>>(4));
        ll tmp = 0;
        if(type.first == 1) tmp += 2;
        if(type.second == 1) tmp += 1;
        nvec[0][tmp].push_back({x,y,type});
        rep(i,0,3)rep(j,0,4){
            for(auto px: nvec[i][j]){
                for(auto nt: px.next())if(nt.type != type){
                    ll tx = 0;
                    if(nt.type.first == 1) tx += 2;
                    if(nt.type.second == 1) tx += 1;
                    nvec[i+1][tx].push_back(nt);
                }
            }
        }
        ll ans = INF;
        // cout << x << " " << y << " " << type.first << " " << type.second << endl;
        rep(i,0,4)rep(j,0,4)rep(k,0,4){
            for(auto ku1:vec[i][k])for(auto ku2:nvec[j][k]){
                chmin(ans,calc(ku1.x-ku2.x, ku1.y-ku2.y, ku1.type.first, ku1.type.second)+i+j);
                // cout << i << " " << j << " " << k << " " << ku2.x << " " << ku2.y << " " << ans << endl;
            }
        }
        cout << ans << endl;
    }
    return 0;
}