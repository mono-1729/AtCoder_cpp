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
//constexpr ll MOD = 1000000007;
constexpr ll MOD = 998244353;
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
    ll n; cin >> n;
    vector<ll> sum(61,0);
    vector<mint> pow3(61,1);
    rep(i,1,61) sum[i] = sum[i-1]+(1LL<<i);
    rep(i,1,61) pow3[i] = pow3[i-1]*3;
    map<ll,mint> mp;
    mp[0] = 1;
    mint ans = 0;
    rrep(i,60,0){
        map<ll,mint> nmp;
        for(auto [num, cnt] : mp){
            if(num+sum[i] <= n) ans += cnt*pow3[i];
            else if(num <= n) nmp[num] += cnt;
            if(num+sum[i]+(1LL<<i) <= n) ans += cnt*pow3[i];
            else if(num + (1LL<<i) <= n) nmp[num+(1LL<<i)] += cnt;
            if(num + (1LL<<(i+1)) <= n) nmp[num+(1LL<<(i+1))] += cnt;
        }
        swap(mp, nmp);
    }
    cout << ans.val() << endl;
    return 0;
}