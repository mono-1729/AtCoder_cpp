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

int max_num=100005;
vector<ll> phi(max_num);
vector<mint> dp(max_num);
vector<vector<ll>> divs(max_num);

void init_e(){
    rep(i, 1, max_num){
        for(ll j = i; j < max_num; j += i){
            divs[j].push_back(i);
        }
    }
	rep(i,0,max_num) phi[i] = i;
    rep(i,2,max_num) {
        if(phi[i] == i) {
            for(ll j = i; j < max_num; j += i) {
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
}

int main() {
    init_e();
    ll n; cin >> n;
    vector<ll> a(n);
    vector<mint> pow2(n+1, 1);
    rep(i,0,n) pow2[i+1] = pow2[i] * 2;
    rep(i,0,n) cin >> a[i];
    mint ans = 0;
    rep(i,0,n){
        ans *= 2;
        for(auto x: divs[a[i]]){
            ans += dp[x];
            dp[x] += pow2[i] * phi[x];
        }
        cout << ans.val() << endl;
    }
    return 0;
}