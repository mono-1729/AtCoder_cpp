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
    ll n; cin >> n;
    vector<ll> x(n), y(n);
    rep(i,0,n) cin >> x[i] >> y[i];
    rep(i,0,n){
        if(abs(x[i]+y[i])%2 != abs(x[0]+y[0])%2){
            cout << -1 << endl;
            return 0;
        }
    }
    vector<ll> arms;
    rrep(i,30,0) arms.push_back(1LL<<i);
    if((x[0]+y[0])%2 == 0) arms.push_back(1);
    cout << arms.size() << endl;
    for(auto l: arms) cout << l << " ";
    cout << endl;
    rep(i,0,n){
        for(auto l: arms){
            if(abs(x[i]) > abs(y[i])){
                if(x[i] > 0){
                    cout << "R";
                    x[i] -= l;
                }else{
                    cout << "L";
                    x[i] += l;
                }
            }else{
                if(y[i] > 0){
                    cout << "U";
                    y[i] -= l;
                }else{
                    cout << "D";
                    y[i] += l;
                }
            }
        }
        cout << endl;
    }
    
    return 0;
}