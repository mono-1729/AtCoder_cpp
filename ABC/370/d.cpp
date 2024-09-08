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

int main() {
    ll h, w, q; cin >> h >> w >> q;
    vector<set<ll>> row(h), col(w);
    rep(i,0,h)rep(j,0,w){
        row[i].insert(j);
        col[j].insert(i);
    }
    ll ans = h*w;
    rep(i,0,q){
        ll r, c; cin >> r >> c;
        r--, c--;
        if(row[r].find(c) != row[r].end()){
            ans--;
            row[r].erase(c);
            col[c].erase(r);
            continue;
        }
        auto itr = row[r].lower_bound(c);
        if(itr != row[r].end()){
            ll nc = *itr;
            ans--;
            row[r].erase(nc);
            col[nc].erase(r);
        }
        itr = col[c].lower_bound(r);
        if(itr != col[c].end()){
            ll nr = *itr;
            ans--;
            row[nr].erase(c);
            col[c].erase(nr);
        }
        itr = row[r].lower_bound(c);
        if(itr != row[r].begin()){
            itr--;
            ll nc = *itr;
            ans--;
            row[r].erase(nc);
            col[nc].erase(r);
        }
        itr = col[c].lower_bound(r);
        if(itr != col[c].begin()){
            itr--;
            ll nr = *itr;
            ans--;
            row[nr].erase(c);
            col[c].erase(nr);
        }
    }
    cout << ans << endl;
    return 0;
}