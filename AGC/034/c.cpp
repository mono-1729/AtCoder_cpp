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
    ll n, x; cin >> n >> x;
    vector<tuple<ll,ll,ll,ll>> vec;
    ll cnt = 0;
    rep(i,0,n){
        ll b, l, u; cin >> b >> l >> u;
        cnt += b * l;
        vec.push_back({b, l, u, x});
    }
    sort(vec.begin(), vec.end(), [](const auto& p, const auto& q){
        auto [pb, pl, pu, px] = p;
        auto [qb, ql, qu, qx] = q;
        return pb*pl+(px-pb)*pu > qb*ql+(qx-qb)*qu;
    });

    auto solve = [&](ll mid) -> bool {
        ll use = mid/x;
        ll num = cnt;
        rep(i,0,use){
            auto [b, l, u, _] = vec[i];
            num -= b*l + u*(x-b);
            mid -= x;
        }
        ll maxi = 0;
        if(use < n){
            auto [b2, l2, u2, x2] = vec[use];
            rep(i,0,use){
                auto [b, l, u, _] = vec[i];
                ll tmp;
                if(mid <= b) tmp = l*mid;
                else tmp = l*b + u*(mid-b);
                tmp -= b*l + u*(x-b);
                tmp += b2*l2 + u2*(x2-b2);
                chmax(maxi, tmp);
            }
            rep(i,use,n){
                auto [b, l, u, _] = vec[i];
                ll tmp;
                if(mid <= b) tmp = l*mid;
                else tmp = l*b + u*(mid-b);
                chmax(maxi, tmp);
            }
        }
        num -= maxi;
        return num <= 0;
    };
    
    ll ng = -1, ok = x*n;

    while(ok-ng > 1){
        ll mid = (ng+ok)/2;
        if(solve(mid)) ok = mid;
        else ng = mid;
    }

    cout << ok << endl;
    return 0;
}