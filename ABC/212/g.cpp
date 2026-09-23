#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <stdlib.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define inr(l, x, r) (l <= x && x < r)
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define all(x) (x).begin(), (x).end()
//constexpr ll MOD = 1000000007;
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint998244353;

ll gcd(ll a, ll b){
    if(b == 0) return a;
    if(a%b == 0){
      return b;
    }else{
      return gcd(b, a%b);
    }
}

ll lcm(ll a, ll b){
    return a*b / gcd(a, b);
}

ll powMod(ll x, ll n, ll mod) {
    if (n == 0) return 1 % mod;
    ll val = powMod(x, n / 2, mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}

int main() {
    ll p; cin >> p;
    vector<ll> div;
    rep(i,1,p){
        if(i*i >= p-1){
            if(i*i == p-1) div.push_back(i);
            break;
        }
        if((p-1)%i != 0) continue;
        div.push_back(i);
        div.push_back((p-1)/i);
    }
    sort(all(div));
    ll n = div.size();
    vector<mint> num(n);
    mint ans = 0;

    rep(i,0,n){
        ll x = div[i];
        num[i] += (p-1)/x;
        rep(j,i+1,n){
            if(div[j]%x == 0) num[j] -= num[i];
        }
        ans += num[i]*((p-1)/x);
    }

    cout << (ans+1).val() << endl;
    return 0;
}