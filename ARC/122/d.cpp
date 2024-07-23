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
    vector<ll> a(2*n);
    rep(i,0,2*n) cin >> a[i];
    sort(a.begin(), a.end());
    auto solve2 = [&](auto self, int digit, int l1, int r1, int l2, int r2) -> ll {
        if(digit == -1 || (r1 - l1 == 1 && r2 - l2 == 1)) return a[l1] ^ a[l2];
        int border1 = l1, border2 = l2;
        while(border1 < r1 && (((a[border1] >> digit) & 1) == 0)) border1++;
        while(border2 < r2 && (((a[border2] >> digit) & 1) == 0)) border2++;
        ll res = INF;
        if(border1 != l1){
            if(border2 == l2) chmin(res, self(self, digit-1, l1, border1, l2, r2));
            else chmin(res, self(self, digit-1, l1, border1, l2, border2));
        }
        if(border1 != r1){
            if(border2 == r2) chmin(res, self(self, digit-1, border1, r1, l2, r2));
            else chmin(res, self(self, digit-1, border1, r1, border2, r2));
        }
        return res;
    };
    auto solve = [&](auto self, int digit, int l, int r) -> ll {
        if(digit == -1 || l == r) return 0;
        int border = l;
        while(border < r && (((a[border] >> digit) & 1) == 0)) border++;
        // cout << digit << " " << l << " " << border << " " << r << endl;
        if((border-l) % 2 == 0) return max(self(self, digit-1, l, border), self(self, digit-1, border, r));
        return solve2(solve2, digit - 1, l, border, border, r);
    };
    cout << solve(solve, 29, 0, 2*n) << endl;
    return 0;
}