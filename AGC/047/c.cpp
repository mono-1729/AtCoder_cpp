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

using mint = modint;

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

ll powM(ll x, ll n, ll mod) {
    if (n == 0) return 1 % mod;
    ll val = powM(x, n / 2, mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}
int calc_primitive_root(int mod) {
    if (mod == 2) return 1;
    if (mod == 167772161) return 3;
    if (mod == 469762049) return 3;
    if (mod == 754974721) return 11;
    if (mod == 998244353) return 3;
    int divs[20] = {};
    divs[0] = 2;
    int cnt = 1;
    long long x = (mod - 1) / 2;
    while (x % 2 == 0) x /= 2;
    for (long long i = 3; i * i <= x; i += 2) {
        if (x % i == 0) {
            divs[cnt++] = i;
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) divs[cnt++] = x;
    for (int g = 2;; g++) {
        bool ok = true;
        for (int i = 0; i < cnt; i++) {
            if (powM(g, (mod - 1) / divs[i], mod) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
}

int main() {
    modint::set_mod(200003);
    ll p = 200003;
    ll n; cin >> n;
    ll r = calc_primitive_root(p);
    vector<ll> num(p-1,1), pow2(p-1);
    rep(i,0,p-2) num[i+1] = (num[i]*r)%p;
    unordered_map<ll,ll> mp;
    rep(i,0,p-1) mp[num[i]] = i;
    vector<ll> cnt(p-1,0);
    ll ans = 0;
    rep(i,0,n){
        ll a; cin >> a;
        if(a == 0) continue;
        cnt[mp[a]]++;
        ans -= (a*a)%p;
    }
    vector<ll> conv = convolution_ll(cnt,cnt);
    rep(i,0,conv.size()){
        ans += conv[i]*num[i%(p-1)];
    }
    cout << ans/2 << endl;
    return 0;
}