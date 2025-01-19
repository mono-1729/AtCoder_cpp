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
    ll n, m; cin >> n >> m;
    vector<ll> p(n);
    rep(i,0,n) cin >> p[i];
    auto solve = [&](ll x) -> pll {
        ll cnt = 0;
        ll sum = m;
        vector<ll> nokori(n);
        rep(i,0,n){
            ll left = (x+p[i])/p[i]/2;
            nokori[i] = (left*2 +1)*p[i];
            if(left == 0) continue;
            if((sum/left)/left < p[i]) return {-1,-1};
            cnt += left;
            sum -= p[i]*left*left;
        }
        sort(nokori.begin(),nokori.end());
        rep(i,0,n){
            if(sum < nokori[i]) break;
            sum -= nokori[i];
            cnt++;
        }
        // cout << x << " " << cnt << endl;
        return {1,cnt};
    };
    ll l = 0, r = INF;
    while(r - l > 1){
        ll mid = (l + r) / 2;
        if(solve(mid).first == 1) l = mid;
        else r = mid;
    }
    cout << solve(l).second << endl;
    return 0;
}