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
    ll n, d; cin >> n >> d;
    vector<ll> xdist(4000005), ydist(4000005);
    vector<int> x(n), y(n);
    ll xsum = 0, ysum = 0;
    rep(i,0,n){
        cin >> x[i] >> y[i];
        x[i] += 2000001;
        y[i] += 2000001;
        xsum += x[i];
        ysum += y[i];
    }
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    rep(i,0,4000004){
        xdist[i] = xsum;
        ydist[i] = ysum;
        int xk = upper_bound(x.begin(), x.end(), i) - x.begin();
        int yk = upper_bound(y.begin(), y.end(), i) - y.begin();
        xsum += xk - (n-xk);
        ysum += yk - (n-yk);
    }
    ll miny = 0;
    rep(i,0,4000004){
        if(ydist[i] < ydist[miny]) miny = i;
    }
    ll ans = 0;
    rep(i,0,4000004){
        ll xd = xdist[i];
        ll y = ydist[miny];
        if(xd+y > d) continue;
        ll l, r;
        l = miny; r = 4000004;
        while(r-l > 1){
            ll m = (l+r)/2;
            if(ydist[m]+xd > + d) r = m;
            else l = m;
        }
        ans += l - miny + 1;
        l = 0; r = miny;
        while(r-l > 1){
            ll m = (l+r)/2;
            if(ydist[m]+xd > d) l = m;
            else r = m;
        }
        ans += miny - r;
    }
    cout << ans << endl;
    return 0;
}