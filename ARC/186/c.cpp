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

struct boxset {
    multiset<pll> minst, otherst;
    ll border;
    ll cost = 0;
    void insert(pll p){
        auto [x,y] = p;
        if(minst.size() < border){
            minst.insert({y,x});
            cost += y-1;
        }else if(border > 0 && minst.rbegin()->first > y){
            auto ep = *minst.rbegin();
            minst.erase(minst.find(ep));
            minst.insert({y,x});
            otherst.insert(ep);
            cost += y-ep.first;
        }else{
            otherst.insert({y,x});
        }
    }
    bool erase(pll p){
        auto [x,y] = p;
        if(otherst.count({y,x})) otherst.erase(otherst.find({y,x}));
        else{
            minst.erase(minst.find({y,x}));
            cost -= y-1;
            if(!otherst.empty()){
                auto ep = *otherst.begin();
                otherst.erase(otherst.begin());
                minst.insert(ep);
                cost += ep.first-1;
            }else return true;
        }
        return minst.size() != border;
    }
};

int main() {
    ll t; cin >> t;
    while(t--){
        ll n, m; cin >> n >> m;
        vector<ll> v(n), p(n);
        vector<pll> vp(n);
        rep(i,0,n){
            cin >> v[i] >> p[i];
            vp[i] = {v[i], p[i]};
        }
        sort(vp.begin(), vp.end());
        boxset bs;
        bs.border = m-1;
        rep(i,0,n) bs.insert(vp[i]);
        ll ans = 0, num = 0;
        rep(i,0,n){
            if(bs.erase(vp[i])) break;
            num += max(0LL, vp[i].first-vp[i].second);
            chmax(ans, num-bs.cost);
        }
        cout << ans << endl;
    }
    return 0;
}