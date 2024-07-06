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

struct rect {
    int h; mint w;
    rect(int h, mint w): h(h), w(w) {};
};

struct D {
    mint tot;
    stack<rect> s;
    D(){}
    void add(int h, mint w){
        while(s.size() && s.top().h <= h) {
            auto [nh,nw] = s.top();
            tot -= nw*nh;
            w += nw;
            s.pop();
        }
        tot += w*h;
        s.emplace(h,w);
    }
};

int main() {
    ll n; cin >> n;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    D dmax, dmin;
    dmax.add(a[0],1);dmin.add(-a[0],1);
    mint now = 0;
    rep(i,0,n){
        now = dmax.tot + dmin.tot;
        if(i == n-1) continue;
        dmax.add(a[i+1],now);
        dmin.add(-a[i+1],now);
    }
    cout << now.val() << endl; 
    return 0;
}