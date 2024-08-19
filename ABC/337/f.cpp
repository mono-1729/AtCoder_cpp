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
    ll n, m, k; cin >> n >> m >> k;
    vector<ll> c(n*2);
    rep(i,0,n) cin >> c[i], c[i]--, c[n+i] = c[i];
    vector<ll> colnum(n,0), colsum(n,0), boxcnt(n,0), coluse(n,0);
    rep(i,0,n) colsum[c[i]]++;
    ll boxsum = 0, use = 0, r = 0;
    rep(l,0,n){
        auto add = [&](ll color, ll num) -> void {
            use -= coluse[color];
            boxsum -= boxcnt[color];
            colnum[color] += num;
            boxcnt[color] = (colnum[color]+k-1)/k;
            coluse[color] = min(colsum[color], boxcnt[color]*k);
            boxsum += boxcnt[color];
            use += coluse[color];
        };
        while(r < n+l && boxsum < m){
            add(c[r], 1);
            r++;
        }
        cout << use << endl;
        add(c[l], -1);
    }
    return 0;
}