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

ll maxnum=1000005;
vector<ll> fac(maxnum), inv(maxnum), finv(maxnum);
void init_fac(){
    inv[1] = 1;
    rep(i, 2, maxnum){
        inv[i] = MOD-MOD/i*inv[MOD%i]%MOD;
    }
}

int main() {
    init_fac();
    ll n; cin >> n;
    vector<ll> nums(1000001, 0);
    vector<mint> gcdinv(1000001);
    rep(i,1,1000001) gcdinv[i] = inv[i];
    rep(i,1,1000001){
        for(int j = 2; i*j <= 1000000; j++) gcdinv[i*j] -= gcdinv[i];
    }
    rep(i,0,n){
        ll a; cin >> a;
        nums[a]++;
    }
    mint ans = 0;
    rep(i,1,1000001){
        mint sum = 0;
        for(ll j = 1; i*j <= 1000000; j++){
            ans += gcdinv[i] * sum * nums[i*j] * i * j;
            ans += gcdinv[i] * (nums[i*j] * (nums[i*j] - 1)/2) * i * i * j * j;
            sum += nums[i*j] * i * j;
        }
    }
    cout << ans.val() << endl;
    return 0;
}