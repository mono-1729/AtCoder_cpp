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

using S = struct{
    ll evenmin;
    ll evenidx;
    ll oddmin;
    ll oddidx;
};
S op(S x1, S x2) {
    ll nem,neid,nom,noid;
    if(x1.evenmin<x2.evenmin){
        nem = x1.evenmin;
        neid = x1.evenidx;
    }
    else{
        nem = x2.evenmin;
        neid = x2.evenidx;
    }
    if(x1.oddmin<x2.oddmin){
        nom = x1.oddmin;
        noid = x1.oddidx;
    }
    else{
        nom = x2.oddmin;
        noid = x2.oddidx;
    }
    return {nem,neid,nom,noid};
} 
S e() {return {INF,-1,INF,-1};}


int main() {
    ll n; cin >> n;
    vector<ll> p(n);
    rep(i, 0, n) cin >> p[i];
    segtree<S,op,e> seg(n);
    rep(i, 0, n){
        if(i%2 == 0) seg.set(i,{p[i],i,INF,-1});
        else seg.set(i,{INF,-1,p[i],i});
    }
    vector<vector<ll>> g(n+1);
    vector<pll>  nums = {{-1,-1}};
    auto solve = [&](auto solve, ll par, ll l, ll r, ll rev)->void{
        if(l == r) return;
        if(par < 0 || n < par) cout << par << endl;
        if(rev){
            auto res = seg.prod(l,r);
            auto res2 = seg.prod(res.oddidx+1,r);
            ll idx = nums.size();
            g[par].push_back(idx);
            nums.push_back({res.oddmin,res2.evenmin});
            solve(solve, idx, l, res.oddidx, rev);
            solve(solve, idx, res.oddidx+1,res2.evenidx, 1-rev);
            solve(solve, idx, res2.evenidx+1, r, rev);
        }
        else{
            auto res = seg.prod(l,r);
            auto res2 = seg.prod(res.evenidx+1,r);
            ll idx = nums.size();
            g[par].push_back(idx);
            nums.push_back({res.evenmin,res2.oddmin});
            solve(solve, idx, l, res.evenidx, rev);
            solve(solve, idx, res.evenidx+1,res2.oddidx, 1-rev);
            solve(solve, idx, res2.oddidx+1, r, rev);
        }
    };
    solve(solve, 0, 0, n, 0);
    priority_queue<tuple<ll,ll,ll>, vector<tuple<ll,ll,ll>>, greater<tuple<ll,ll,ll>>> pq;
    vector<ll> check(n+1,0);
    check[0] = 1;
    for(auto x:g[0]){
        pq.push({nums[x].first, nums[x].second, x});
        check[x] = 1;
    } 
    while(!pq.empty()){
        ll x, y, idx; tie(x, y, idx) = pq.top();
        pq.pop();
        cout << x << " " << y << " ";
        for(auto next: g[idx]){
            if(check[next]) continue;
            pq.push({nums[next].first,nums[next].second, next});
            check[next] = 1;
        }
    }
    cout<<endl;
    return 0;
}