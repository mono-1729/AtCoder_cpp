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
    ll n, x; cin >> n >> x;
    vector<ll> a(n);
    vector<mint> cnt(1000005);
    rep(i,0,n) cin >> a[i], cnt[a[i]]++;
    rep(i,0,1000005) if(cnt[i].val() > 3) cnt[i] = 3;
    vector<mint> comb = convolution(cnt, cnt);
    rep(i,0,1000005){
        if(i%2 == 0) comb[i] -= cnt[i/2];
        comb[i] /= 2;
    }
    ll k = -1;
    rrep(i, n-1, 0){
        mint num = comb[x-a[i]];
        if(x-2*a[i] >= 0){
            num -= cnt[x-2*a[i]];
            if(x == a[i]*3) num++;
        }
        if(num != 0){
            k = i;
            break;
        }
    }
    if(k == -1){
        cout << -1 << endl;
        return 0;
    }
    x -= a[k];
    vector<ll> idx(1000005, -1);
    rep(i,0,n){
        if(x-a[i] > 0 && idx[x-a[i]] >= 0){
            cout << idx[x-a[i]]+1 << " " << i+1 << " " << k+1 << endl;
            return 0;
        }
        idx[a[i]] = i;
    }

    return 0;
}