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
    ll n, k; cin >> n >> k;
    vector<ll> r(n);
    rep(i,0,n) cin >> r[i];
    vector<ll> ans(n,1);
    auto add = [&]() -> bool {
        bool res = false;
        rep(i,0,n)if(ans[i] < r[i]) res = true;
        rrep(i,n-1,0){
            if(ans[i] < r[i]){
                ans[i]++;
                break;
            }
            else ans[i] = 1;
        }
        return true;
    };
    while(true){
        ll sum = 0;
        rep(i,0,n) sum += ans[i];
        if(sum%k == 0){
            rep(i,0,n) cout << ans[i] << " ";
            cout << endl;
        }
        if(!add()) break;
    }
    return 0;
}