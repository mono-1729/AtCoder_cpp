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

struct st {
    ll c1 = -INF;
    ll pos1 = INF;
    ll c2 = -INF;
    ll pos2 = INF;
    void insert(ll c, double pos){
        if(pos1 == pos) chmax(c1, c);
        else if(pos2 == pos){
            chmax(c2, c);
            if(c2 > c1){
                swap(c1, c2); swap(pos1, pos2);
            }
        }
        else if(c1 < c){
            swap(c1, c2); swap(pos1, pos2);
            c1 = c, pos1 = pos;
        }else if(c2 < c) c2 = c, pos2 = pos;
    }
};


int main() {
    ll n; cin >> n;
    vector<ll> x(n), y(n), c(n);
    rep(i,0,n) cin >> x[i] >> y[i] >> c[i];
    ll ans = 0;
    ll num = 2e9 + 1;
    map<pair<ll,ll>,st> mp;
    rep(i,0,n)rep(j,i+1,n){
        if(y[i] == y[j]){
            mp[{INF,x[i]+x[j]}].insert(c[i] + c[j], y[i]);
        }else{
            ll xdist = x[j] - x[i], ydist = y[j] - y[i];
            ll g = gcd(abs(xdist), abs(ydist));
            swap(xdist, ydist);
            xdist *= -1;
            xdist /= g; ydist /= g;
            if(xdist < 0) xdist *= -1, ydist *= -1;
            if(xdist * ydist >= 0){
                mp[{(xdist)*num + ydist, xdist*(y[i]+y[j])-ydist*(x[i]+x[j])}].insert(c[i] + c[j], x[i]+x[j]);
            }
            else{
                mp[{-(xdist)*num + ydist, xdist*(y[i]+y[j])-ydist*(x[i]+x[j])}].insert(c[i] + c[j], x[i]+x[j]);
            }
        }
    }
    for(auto [x,y]: mp) chmax(ans,y.c1+y.c2);
    cout << (ans == 0 ? -1 : ans) << endl;
    return 0;
}