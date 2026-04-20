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
    ll k, n; cin >> k >> n;
    if(k == 1){
        rep(i,0,(n+1)/2) cout << 1 << " ";
        cout << endl;
        return 0;
    }
    if(k%2 == 0){
        cout << k/2 << " ";
        rep(i,0,n-1) cout << k << " ";
        cout << endl;
        return 0;
    }
    vector<ll> ans(n,(k+1)/2);
    rep(_,0,n/2){
        rrep(i,n-1,0){
            if(ans[i] != 0){
                ans[i]--;
                if(ans[i] != 0){
                    rep(j,i+1,n) ans[j] = k;
                }
                break;
            }
        }
    }
    for(auto x: ans) if(x) cout << x << " ";
    cout << endl;
    return 0;
}