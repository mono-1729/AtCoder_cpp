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

bool equal(char x, char y){
    return (x == y || x == '?' || y == '?');
}

int main() {
    string a,b,c; cin >> a >> b >> c;
    ll A = a.size(), B = b.size(), C = c.size();
    ll ans = A+B+C;
    vector<bool> ab(20000,false),ac(20000,false),bc(20000,false);
    rep(i,0,A)rep(j,0,B) if(!equal(a[i],b[j])) ab[i-j+10000] = true;
    rep(i,0,A)rep(j,0,C) if(!equal(a[i],c[j])) ac[i-j+10000] = true;
    rep(i,0,B)rep(j,0,C) if(!equal(b[i],c[j])) bc[i-j+10000] = true;
    rep(i,-4000,4001)rep(j,-4000,4001){
        if(ab[i+10000]) continue;
        if(ac[j+10000]) continue;
        if(bc[j-i+10000]) continue;
        ll l = min(min(0LL,i),j);
        ll r = max(max(A,i+B),j+C);
        chmin(ans,r-l);
    }
    cout << ans << endl;
    return 0;
}