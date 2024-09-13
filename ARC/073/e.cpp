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

int main() {
    ll n; cin >> n;
    vector<ll> x(n), y(n);
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    ll rmax = 0, rmin = INF, bmax = 0, bmin = INF;
    ll ans = INF;
    ll pqmax = 0;
    rep(i,0,n){
        cin >> x[i] >> y[i];
        if(x[i] > y[i]) swap(x[i], y[i]);
        chmax(rmax,x[i]);
        chmin(rmin,x[i]);
        chmax(bmax,y[i]);
        chmin(bmin,y[i]);
        pq.push({x[i],i});
        chmax(pqmax,x[i]);
    }
    chmin(ans,(rmax-rmin)*(bmax-bmin));
    ll size = (bmax-rmin);
    while(true){
        auto [a,b] = pq.top();pq.pop();
        chmin(ans,(pqmax-a)*size);
        if(b == -1) break;
        chmax(pqmax,y[b]);
        pq.push({y[b],-1});
    }
    cout << ans << endl;
    return 0;
}