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
    ll d; cin >> d;
    vector<ll> pow10(19,1);
    rep(i,1,19) pow10[i] = pow10[i-1]*10;
    ll ans = 0;
    auto solve = [&](auto solve, ll diff, ll digit, ll dall,ll num) -> void {
        if(dall%2 == 0 && (digit+1)*2 == dall){
            if(diff == d) ans += num;
            return;
        }else if(dall%2 == 1 && digit*2+1 == dall){
            if(diff == d) ans += 10*num;
            return;
        }
        unordered_map<ll,ll> mp;
        // cout << digit << " " << dall-digit-1 << endl;
        if(digit == dall-1){
            rep(i,1,10)rep(j,0,10){
                ll tmp = pow10[digit]*j+pow10[dall-digit-1]*i - (pow10[digit]*i+pow10[dall-digit-1]*j);
                ll next = diff+tmp;
                if(abs(next-d) <= pow10[digit]) mp[next] += num;
            }
        }else{
            rep(i,0,10)rep(j,0,10){
                ll tmp = pow10[digit]*j+pow10[dall-digit-1]*i - (pow10[digit]*i+pow10[dall-digit-1]*j);
                ll next = diff+tmp;
                if(abs(next-d) <= pow10[digit]) mp[next] += num;
            }
        }
        for(auto x: mp) solve(solve, x.first, digit-1, dall, x.second);
    };
    rep(i,1,18) solve(solve, 0, i,i+1, 1);
    cout << ans << endl;
    return 0;
}