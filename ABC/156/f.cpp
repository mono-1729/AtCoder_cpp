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
    ll k, q; cin >> k >> q;
    vector<ll> d_(k), d(k);
    rep(i,0,k) cin >> d_[i];
    while(q--){
        ll n, x, m; cin >> n >> x >> m;
        x %= m;
        n--;
        ll ans = n;
        ll sum = 0;
        ll sum0 = 0;
        rep(i,0,k){
            d[i] = d_[i]%m;
            sum += d[i];
            if(d[i] == 0) sum0++;
        }
        ll cnt = x;
        cnt += sum * (n/k);
        ans -= sum0 * (n/k);
        rep(i,0,n%k){
            cnt += d[i];
            if(d[i] == 0) ans--;
        }
        ans -= cnt/m;
        cout << ans << endl;
    }
    return 0;
}