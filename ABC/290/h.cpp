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
    int t; cin >> t;
    while(t--){
        ll d, k, x; cin >> d >> k >> x;
        ll ans = INF;
        vector<ll> size(d+1,1);
        vector<ll> subtree(d+1);
        rep(i,0,d) size[i+1] = size[i]*k;
        subtree[0] = 1;
        rep(i,1,d+1) subtree[i] = subtree[i-1] + size[i];
        rep(i,0,d+1){
            ll cnt = i == d ? 0 : 1;
            ll sum = subtree[i];
            if(sum < x) continue;
            rrep(j,i,0){
                ll del = (sum-x)/subtree[j];
                cnt += del;
                sum -= del*subtree[j];
            }
            chmin(ans,cnt);
        }
        cout << ans << endl;
    }
    return 0;
}