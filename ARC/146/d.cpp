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

ll powMod(ll x, ll n, ll mod) {
    if (n == 0) return 1 % mod;
    ll val = powMod(x, n / 2, mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}

int main() {
    ll n, m, k; cin >> n >> m >> k;
    vector<ll> p(k), x(k), q(k), y(k);
    vector<vector<tuple<ll,ll,ll>>> vec(n);
    queue<pll> que;
    rep(i,0,k){
        cin >> p[i] >> x[i] >> q[i] >> y[i];
        p[i]--, q[i]--;
        vec[p[i]].push_back({x[i],q[i],y[i]});
        vec[q[i]].push_back({y[i],p[i],x[i]});
        if(x[i] == 1 && y[i] != 1) que.push({q[i],y[i]});
        if(x[i] != 1 && y[i] == 1) que.push({p[i],x[i]});
    }
    rep(i,0,n) sort(all(vec[i]));
    auto no = [&]() {
        cout << -1 << endl;
        exit(0);
    };
    vector<ll> ans(n,1);
    while(!que.empty()){
        auto [id,num] = que.front(); que.pop();
        if(ans[id] >= num) continue;
        auto it = lower_bound(all(vec[id]),make_tuple(ans[id],-1,-1));
        while(it != vec[id].end() && get<0>(*it) <= num){
            auto [a,b,c] = *it;
            if(a < num) que.push({b,c+1});
            else que.push({b,c});
            it = next(it);
        }
        ans[id] = num;
    }
    rep(i,0,k){
        if(ans[p[i]] < x[i] && ans[q[i]] < y[i]) continue;
        if(ans[p[i]] == x[i] && ans[q[i]] == y[i]) continue;
        if(ans[p[i]] > x[i] && ans[q[i]] > y[i]) continue;
        no();
    }
    ll sum = 0;
    for(auto a: ans){
        sum += a;
        if(a > m) no();
    }
    cout << sum << endl;
    return 0;
}