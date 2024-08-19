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
    ll n, x, d; cin >> n >> x >> d;
    if(d == 0){
        if(x != 0) cout << n+1 << endl;
        else cout << 1 << endl;
        return 0;
    }else if(d < 0){
        x = x + d*(n-1);
        d = -d;
    }
    vector<ll> sum(n+1);
    rep(i,0,n) sum[i+1] = sum[i] + x + i*d;
    unordered_map<ll,multiset<pll>> mp;
    rep(i,0,n+1){
        ll mini = sum[i];
        ll maxi = (sum[n]-sum[n-i]);
        ll mod = mini % d; if(mod < 0) mod += d;
        ll l = mini/d; if(mini%d < 0) l--;
        ll r = maxi/d + 1; if(maxi%d < 0) r--;
        mp[mod].insert({l,0});
        mp[mod].insert({r,1});
    }
    ll ans = 0;
    for(auto [mod,st]: mp){
        ll cnt = 0;
        ll pre = 0;
        for(auto [idx,type] :st){
            if(cnt > 0) ans += idx-pre;
            if(type == 0) cnt++;
            else cnt--;
            pre = idx;
        }
    }
    cout << ans << endl;
    return 0;
}