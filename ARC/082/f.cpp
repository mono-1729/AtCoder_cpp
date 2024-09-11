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

struct timer{
    ll max_sand;
    pll left,right;
    ll pre = 0;
    ll rnum = 0;
    timer(ll x){
        max_sand = x;
        left = {0,0};
        right = {x,x};
    }
    void reverse(ll time){
        ll len = time - pre;
        auto [l1,l2] = left;
        auto [r1,r2] = right;
        if(rnum%2 == 0){
            left = {max_sand-max(0LL,l1-len),l2+max(0LL,len-l1)};
            right = {max_sand-max(0LL,r1-len),r2};
        }else{
            left = {max_sand-max(0LL,l1-len),l2};
            right = {max_sand-max(0LL,r1-len),r2-max(0LL,len-r1)};
        }
        pre = time;
        rnum++;
    }
    ll answer(ll time, ll start){
        auto [l1,l2] = left;
        auto [r1,r2] = right;
        // cout << l1 << " " << l2 << " " << r1 << " " << r2 << endl;
        ll res;
        if(start <= l2) res = max(0LL,l1-(time-pre));
        else if(start >= r2) res = max(0LL,r1-(time-pre));
        else if(rnum%2 == 0) res = max(0LL,l1+(start-l2)-(time-pre));
        else res = max(0LL,l1-(start-l2)-(time-pre));
        return rnum % 2 == 0 ? res : max_sand-res;
    }
};

int main() {
    ll x, k; cin >> x >> k;
    vector<ll> r(k);
    vector<tuple<ll,ll,ll>> query;
    rep(i,0,k){
        cin >> r[i];
        query.push_back({r[i],-1,-1});
    }
    ll q; cin >> q;
    vector<ll> ans(q);
    rep(i,0,q){
        ll t, a; cin >> t >> a;
        query.push_back({t,i,a});
    }
    sort(query.begin(), query.end());
    timer ti(x);
    for(auto [a,b,c]: query){
        if(b == -1) ti.reverse(a);
        else ans[b] = ti.answer(a,c);
    }
    for(auto a: ans) cout << a << endl;
    return 0;
}