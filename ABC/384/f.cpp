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
    ll n; cin >> n;
    vector<ll> a(n);
    ll all = 0;
    rep(i,0,n) cin >> a[i], all += a[i];
    ll sum = 0, ans = 0;
    rrep(i,24,1){
        ll div = (1<<i);
        unordered_map<ll, pll> mp;
        rep(j,0,n) mp[a[j]%div].first += a[j], mp[a[j]%div].second++;
        ll now = 0;
        vector<ll> keys;
        for(auto x: mp) keys.push_back(x.first);
        for(ll x: keys){
            if(mp[(x == 0 ? 0 : div-x)].second) now += mp[x].first*mp[(x == 0 ? 0 : div-x)].second+mp[x].second*mp[(x == 0 ? 0 : div-x)].first;
        }
        now -= sum;
        ans += now/div;
        sum += now;
    }
    ans += all*n*2-sum;
    rep(i,0,n){
        ll x = a[i]+a[i];
        while(x%2 == 0) x /= 2;
        ans += x;
    }
    cout << ans/2 << endl;
    return 0;
}