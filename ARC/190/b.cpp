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

ll powMod(ll x, ll n) {
    if (n == 0) return 1 % MOD;
    ll val = powMod(x, n / 2);
    val *= val;
    val %= MOD;
    if (n % 2 == 1) val *= x;
    return val % MOD;
}

ll maxnum=10000003;
vector<ll> fac(maxnum), inv(maxnum), finv(maxnum);
void init_fac(){
    fac[0] = fac[1] = 1;
    inv[1] = 1;
    finv[0] = finv[1] = 1;
    rep(i, 2, maxnum){
        fac[i] = fac[i-1]*i%MOD;
        inv[i] = MOD-MOD/i*inv[MOD%i]%MOD;
        finv[i] = finv[i-1]*inv[i]%MOD;
    }
}
ll nCr(ll n, ll r){
    if(n < 0 or n-r < 0 or r < 0) return 0;
    return fac[n]*(finv[n-r]*finv[r]%MOD)%MOD;
}
ll nHr(ll n, ll r){
    return nCr(n+r-1, r);
}

int main() {
    init_fac();
    ll n, a, b; cin >> n >> a >> b;
    a--; b--;
    ll q; cin >> q;
    vector<mint> anslr(n+1, 1), ansud(n+1, 1);
    vector<mint> pow2(n*2+1, 1);
    rep(i,1,n*2+1) pow2[i] = pow2[i-1]*2;
    vector<ll> query(q);
    rep(i,0,q) cin >> query[i];
    rrep(i,n-1,0){
        {
            ansud[i] = ansud[i+1]*2;
            if(a+1 <= n-i) ansud[i] -= nCr(n-i-1, a);
            if(n-a <= n-i) ansud[i] -= nCr(n-i-1, n-a-1);
        }
        {
            anslr[i] = anslr[i+1]*2;
            if(b+1 <= n-i) anslr[i] -= nCr(n-i-1, b);
            if(n-b <= n-i) anslr[i] -= nCr(n-i-1, n-b-1);
        }
    }
    // rrep(i,n,0) cout << anslr[i].val() << " " << ansud[i].val() << endl;
    rep(i,0,q){
        mint in = anslr[query[i]-1]*ansud[query[i]-1]*pow2[max(0LL, 2*query[i]-4)];
        mint all = anslr[query[i]]*ansud[query[i]]*pow2[2*query[i]-2];
        // cout << all.val() << " " << in.val() << endl;
        cout << (all-in).val() << endl;
    }
    return 0;
}