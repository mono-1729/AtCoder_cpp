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
    rep(i,0,n) cin >> a[i];
    vector<ll> right(n,0), left(n,0);
    rep(i,1,n){
        ll x1 = a[i-1], x2 = a[i];
        if(x1 >= x2){
            while(x1 >= x2 * 4){
                x2 *= 4;
                left[i]-=2;
            }
        }else{
            while(x1 < x2){
                x1 *= 4;
                left[i]+=2;
            }
        }
    }
    reverse(a.begin(), a.end());
    rep(i,1,n){
        ll x1 = a[i-1], x2 = a[i];
        if(x1 >= x2){
            while(x1 >= x2 * 4){
                x2 *= 4;
                right[i]-=2;
            }
        }else{
            while(x1 < x2){
                x1 *= 4;
                right[i]+=2;
            }
        }
    }
    vector<vector<ll>> ldp(n+1, vector<ll>(31,0)), rdp(n+1, vector<ll>(31,0));
    rep(i,0,31) ldp[1][i] = i, rdp[1][i] = i;
    rep(i,1,n){
        rep(j,0,31){
            if(j+left[i] >= 31) ldp[i+1][j] = ldp[i+1][j-1] + i + 1;
            else if(j+left[i] < 0) ldp[i+1][j] = ldp[i][0] + j;
            else ldp[i+1][j] = ldp[i][j+left[i]] + j;
            if(j+right[i] >= 31) rdp[i+1][j] = rdp[i+1][j-1] + i + 1;
            else if(j+right[i] < 0) rdp[i+1][j] = rdp[i][0] + j;
            else rdp[i+1][j] = rdp[i][j+right[i]] + j;
        }
    }
    ll ans = INF;
    rep(i,0,n+1){
        chmin(ans, ldp[i][0] + rdp[n-i][0] + i);
        // cout << ldp[i][0] << " " << rdp[n-i][0] << " " << i << endl;
    }
    cout << ans << endl;
    return 0;
}