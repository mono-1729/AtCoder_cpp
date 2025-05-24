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
#define all(x) (x).begin(), (x).end()
constexpr ll MOD = 1000000007;
//constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint1000000007;

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
    ll b = 450;
    vector<vector<mint>> dpl(b+1,vector<mint>(m+1,0)), dpr(b+1,vector<mint>(m+1,0));
    for(int i = 0; i <= m; i += n) dpl[0][i] = 1;
    dpr[0][0] = 1;
    rep(i,1,b+1){
        ll p = i*(i+1)/2;
        vector<mint> modl(p),modr(p);
        rep(j,0,m+1){
            modl[j%p] += dpl[i-1][j];
            dpl[i][j] = modl[j%p];
            modr[j%p] += dpr[i-1][j];
            dpr[i][j] = modr[j%p];
        }
    }
    mint ans = 0;
    rep(l,0,min(n,b)){
        ll mm = m-l*(l+1)/2;
        if(mm < 0) continue;
        rep(lnum,0,mm+1) ans += dpl[l][lnum]*dpr[min(b,n-l-1)][mm-lnum];
        // cout << ans.val() << endl;
    }
    cout << ans.val() << endl;
    return 0;
}