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
    vector<ll> keta(n+1);
    vector<mint> pow10(7,1), fac(n+1,1);
    rep(i,1,n+1) keta[i] = to_string(i).size();
    rep(i,1,7) pow10[i] = pow10[i-1]*10;
    rep(i,1,n) fac[i] = fac[i-1]*i;
    vector<mint> f;
    {
        queue<vector<mint>> q;
        rep(i,1,n+1) q.push({1,pow10[keta[i]]});
        while(q.size() > 1){
            vector<mint> a = q.front();q.pop();
            vector<mint> b = q.front();q.pop();
            q.push(convolution(a,b));
        }
        f = q.front();
    }
    mint ans = 0;
    rep(i,1,7){
        if(keta[n] < i) break;
        mint sum = 0;
        rep(j,1,n+1) if(keta[j] == i) sum += j;
        vector<mint> f_ = f;
        rep(j,0,n){
            ans += sum * fac[j] * fac[n-j-1] * f_[j];
            f_[j+1] -= f_[j]*pow10[i];
            f_[j] = 0;
        }
    }
    cout << ans.val() << endl;
    return 0;
}