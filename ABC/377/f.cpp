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

using S = long long;
S op(S x1, S x2) {
    return x1+x2;
} 
bool f(S x){
    return 1;
}
S e() {return 0;}

int main() {
    ll n, m; cin >> n >> m;
    vector<ll> row, col, diag;
    vector<ll> a(m), b(m);
    rep(i,0,m) cin >> a[i] >> b[i], a[i]--, b[i]--;
    rep(i,0,m){
        row.push_back(a[i]);
        col.push_back(b[i]);
    }
    sort(row.begin(), row.end());
    sort(col.begin(), col.end());
    row.erase(unique(row.begin(), row.end()), row.end());
    col.erase(unique(col.begin(), col.end()), col.end());
    ll ans = n*(ll)row.size() + n*(ll)col.size() - (ll)row.size()*(ll)col.size();
    rep(i,0,m){
        ll start = a[i]-b[i], end = a[i]+n-b[i];
        ll start2 = b[i]-a[i], end2 = b[i]+n-a[i];
        diag.push_back(start);
        ans += min(end,n-1)-max(start,0LL) + 1;


    }
    return 0;
}